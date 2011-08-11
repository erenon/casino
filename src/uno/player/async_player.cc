#include <node/v8.h>
#include <node/node.h>
#include <string>
#include <stdexcept>

#include "async_player.h"
#include "../action/action.h"
#include "../action/card.h"
#include "../game/async_game.h"
#include "../event/event.h"

namespace Uno { namespace Player {

using namespace v8;
using ::Uno::Game::AsyncGame;
using ::Uno::Player::Player;
using ::Uno::Action::Action;
//Card, CARD_COLOR/VALUE
using namespace ::Uno::Action;
namespace Event = ::Uno::Event;

#define REQ_INT_ARG(I)                                                  \
    if (args.Length() <= (I) || !args[I]->IsInt32()) {                  \
        return ThrowException(Exception::TypeError(                     \
            String::New("Argument " #I " must be an integer")));        \
    }

#define REQ_OBJ_ARG(I)                                                  \
    if (args.Length() <= (I) || !args[I]->IsObject()) {                 \
        return ThrowException(Exception::TypeError(                     \
            String::New("Argument " #I " must be an object")));         \
    }

AsyncPlayer::AsyncPlayer(Handle<Object> jsplayer) {
	HandleScope scope;
	session_id = *String::AsciiValue(jsplayer->Get(String::New("session_id"))->ToString());
	this->jsplayer = Persistent<Object>::New(jsplayer);
}

void AsyncPlayer::setGame(AsyncGame* game) {
	this->game = game;
}

Local<Function> AsyncPlayer::getCallback(const char* cbname) {
	HandleScope scope;
	Local<Function> cb = Local<Function>::Cast(
		jsplayer->Get(String::New(cbname))
	);

	if (!cb->IsFunction()) {
		std::string error("callback not found: ");
		error.append(cbname);
		throw std::invalid_argument(error.c_str());
	}

	return scope.Close(cb);
}

void AsyncPlayer::addCard(Card *card) {
	Player::addCard(card);

	Handle<Value> argument = createCardObject(card);

	Local<Function> addaction_cb = getCallback("addAction");
	TryCatch try_catch;
	addaction_cb->Call(Context::GetCurrent()->Global(), 1, &argument);
	if (try_catch.HasCaught()) {
		node::FatalException(try_catch);
	}
}

void AsyncPlayer::playCard(const Arguments &args) {
	HandleScope scope;

    if (args.Length() <= 0 || !args[0]->IsObject()) {
        throw std::invalid_argument("Argument 0 must be an object");
    }

	Local<Object> picked_card = args[0]->ToObject();

	Local<String> key_color = String::NewSymbol("color");
	Local<String> key_value = String::NewSymbol("value");

	if (picked_card->Has(key_color) == false) {
		throw std::invalid_argument("Malformed card object, no color property.");
	}

	if (picked_card->Has(key_value) == false) {
		throw std::invalid_argument("Malformed card object, no value property.");
	}

	Local<Value> property_color = picked_card->Get(key_color);
	if (property_color->IsString() == false) {
		throw std::invalid_argument("Card color must be string.");
	}

	Local<Value> property_value = picked_card->Get(key_value);
	if (property_value->IsString() == false) {
		throw std::invalid_argument("Card value must be string.");
	}

	CARD_COLOR picked_color;
	try {
		picked_color = Card::stringToColor(
			*String::AsciiValue(property_color->ToString())
		);
	} catch (std::invalid_argument &e) {
		throw;
	}

	CARD_VALUE picked_value;
	try {
		picked_value = Card::stringToValue(
			*String::AsciiValue(property_value->ToString())
		);
	} catch (std::invalid_argument &e) {
		throw;
	}

	card_iterator action;
	for (action = hand.begin(); action < hand.end(); action++) {
		Card* card = static_cast<Card*>(*action);

		// same color and value
		if (card->getColor() == picked_color
		&&  card->getValue() == picked_value
		) {
			try {
				game->takeAction(this, *action);
			} catch (std::invalid_argument &message) {
				throw std::domain_error(message.what());
			}
		}
	}

}

void AsyncPlayer::draw() {
	try {
		game->takeDraw(this);
	} catch (std::invalid_argument &message) {
		throw;
	}
}

Local<Object> AsyncPlayer::createCardObject(Card* card) {
	HandleScope scope;
	Local<Object> jscard = Object::New();

	// set color
	const char* color = NULL;

	switch (card->getColor()) {
	case CARD_COLOR_RED:
		color = "red";
		break;
	case CARD_COLOR_GREEN:
		color = "green";
		break;
	case CARD_COLOR_BLUE:
		color = "blue";
		break;
	case CARD_COLOR_YELLOW:
		color = "yellow";
		break;
	case CARD_COLOR_BLACK:
		color = "black";
		break;
	default:
		color = "?";
		break;
	}

	jscard->Set(
		String::New("color"),
		String::NewSymbol(color)
	);

	// set value
	const char* value = NULL;
#define CASE_CARD_VALUE(V,O) 	\
	case CARD_VALUE_##V: 		\
		value = O; 				\
		break;

	switch (card->getValue()) {
		CASE_CARD_VALUE(0,"0");
		CASE_CARD_VALUE(1,"1");
		CASE_CARD_VALUE(2,"2");
		CASE_CARD_VALUE(3,"3");
		CASE_CARD_VALUE(4,"4");
		CASE_CARD_VALUE(5,"5");
		CASE_CARD_VALUE(6,"6");
		CASE_CARD_VALUE(7,"7");
		CASE_CARD_VALUE(8,"8");
		CASE_CARD_VALUE(9,"9");
		CASE_CARD_VALUE(BLOCK, "block");
		CASE_CARD_VALUE(REVERSE, "reverse");
		CASE_CARD_VALUE(PLUSTWO, "+2");
		CASE_CARD_VALUE(COLORPICK, "colorpicker");
		CASE_CARD_VALUE(PLUSFOUR, "+4");

		default:
			value = "?";
			break;
	}

#undef CASE_CARD_VALUE

	jscard->Set(
		String::New("value"),
		String::NewSymbol(value)
	);

	return scope.Close(jscard);
}

Local<Object> AsyncPlayer::createPlayerObject(Player* player) {
	HandleScope scope;
	Local<Object> jsplayer = Object::New();

	jsplayer->Set(
		String::NewSymbol("name"),
		String::New(player->getName().c_str())
	);

	return scope.Close(jsplayer);
}

void AsyncPlayer::notify(Event::EVENT event_type, void* event) {
	HandleScope scope;

	Local<Object> jsevent = Object::New();
	const char* jstype = "";

	switch (event_type) {
	case Event::EVENT_GAME_START:
	{
		jstype = "game_start";

		jsevent->Set(
			String::NewSymbol("first_card"),
			createCardObject(
				reinterpret_cast<Event::game_start*>(event)->first_card
			)
		);
	}
		break;
	case Event::EVENT_CARD_PLAYED:
	{
		jstype = "card_played";

		Event::card_played* e = reinterpret_cast<Event::card_played*>(event);
		jsevent->Set(
			String::NewSymbol("played_by"),
			createPlayerObject(e->played_by)
		);

		jsevent->Set(
			String::NewSymbol("played_card"),
			createCardObject(e->played_card)
		);
	}
		break;

	case Event::EVENT_GAME_END:
	{
		jstype = "game_end";

		Event::game_end* e = reinterpret_cast<Event::game_end*>(event);
		jsevent->Set(
			String::NewSymbol("winner"),
			createPlayerObject(e->winner)
		);
	}
		break;

	case Event::EVENT_COLORPICK:
	{
		jstype = "colorpick";

		Event::colorpick* e = reinterpret_cast<Event::colorpick*>(event);

		jsevent->Set(
			String::NewSymbol("picked_by"),
			createPlayerObject(e->picked_by)
		);

		const char* color;
		switch (e->color) {
		case CARD_COLOR_RED:
			color = "red";
			break;
		case CARD_COLOR_GREEN:
			color = "green";
			break;
		case CARD_COLOR_BLUE:
			color = "blue";
			break;
		case CARD_COLOR_YELLOW:
			color = "yellow";
			break;
		default:
			color = "?";
			break;
		}

		jsevent->Set(
			String::NewSymbol("color"),
			String::NewSymbol(color)
		);
	}
		break;

	case Event::EVENT_DRAW_CARD:
	{
		jstype = "draw_card";

		Event::draw_card* e = reinterpret_cast<Event::draw_card*>(event);

		jsevent->Set(
			String::NewSymbol("player"),
			createPlayerObject(e->player)
		);

		jsevent->Set(
			String::NewSymbol("card_count"),
			Int32::New(e->card_count)
		);

		break;
	}

	case Event::EVENT_GETS_BLOCKED:
	{
		jstype = "gets_blocked";
		Event::gets_blocked* e = reinterpret_cast<Event::gets_blocked*>(event);

		jsevent->Set(
			String::NewSymbol("gets_blocked"),
			createPlayerObject(e->gets_blocked)
		);

		jsevent->Set(
			String::NewSymbol("blocked_by"),
			createPlayerObject(e->blocked_by)
		);

		break;
	}

	case Event::EVENT_UNO_SAID:
	{
		jstype = "uno_said";
		Event::uno_said* e = reinterpret_cast<Event::uno_said*>(event);

		jsevent->Set(
			String::NewSymbol("said_by"),
			createPlayerObject(e->said_by)
		);

		const char* type = "";
		switch (e->type) {
		case Event::uno_said::GOOD:
			type = "good";
			break;
		case Event::uno_said::BAD:
			type = "bad";
			break;
		case Event::uno_said::FORGOTTEN:
			type = "forgotten";
			break;
		}

		jsevent->Set(
			String::NewSymbol("type"),
			String::NewSymbol(type)
		);

		break;
	}

	case Event::EVENT_PLAYER_JOINED:
	{
		jstype = "player_joined";
		Event::player_joined* e = reinterpret_cast<Event::player_joined*>(event);

		jsevent->Set(
			String::NewSymbol("player"),
			createPlayerObject(e->player)
		);

		break;
	}

	case Event::EVENT_PLAYERS_TURN:
	{
		jstype = "players_turn";
		Event::players_turn* e = reinterpret_cast<Event::players_turn*>(event);

		jsevent->Set(
			String::NewSymbol("player"),
			createPlayerObject(e->player)
		);
		break;
	}

	default:
		/**
		 * @todo fix typo: unknown.
		 */
		jstype = "unknow_event";
		break;

	}

	jsevent->Set(
			String::NewSymbol("event_type"),
			String::New(jstype)
	);

	Handle<Value> argument = jsevent;

	{   // call notify_cb
		Local<Function> notify_cb = getCallback("notify");
		TryCatch try_catch;
		notify_cb->Call(Context::GetCurrent()->Global(), 1, &argument);
		if (try_catch.HasCaught()) {
			node::FatalException(try_catch);
		}
	}
}

#undef REQ_INT_ARG

}} //namespace
