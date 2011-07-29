#include <node/v8.h>
#include <node/node.h>
#include <string>

#include "javascript_player.h"
#include "../action/action.h"
#include "../action/card.h"
#include "../game/game.h"
#include "../event/event.h"


namespace Casino { namespace Uno { namespace Player {

using namespace v8;
using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Action::UnoAction;
using ::Casino::Uno::Action::UnoCard;
using namespace ::Casino::Uno::Action;
namespace Event = ::Casino::Uno::Event;

#define REQ_INT_ARG(I)                                                  \
    if (args.Length() <= (I) || !args[I]->IsInt32()) {                  \
        return ThrowException(Exception::TypeError(                     \
            String::New("Argument " #I " must be an integer")));        \
    }

JavascriptUnoPlayer::JavascriptUnoPlayer(Handle<Object> jsplayer) {
	HandleScope scope;
	session_id = *String::AsciiValue(jsplayer->Get(String::New("session_id"))->ToString());
	this->jsplayer = Persistent<Object>::New(jsplayer);
}

Local<Function> JavascriptUnoPlayer::getCallback(const char* cbname) {
	HandleScope scope;
	Local<Function> cb = Local<Function>::Cast(
		jsplayer->Get(String::New(cbname))
	);

	if (!cb->IsFunction()) {
		throw "callback not found";
	}

	return scope.Close(cb);
}
/**
 * @todo handle invalid move
 */
UnoAction* JavascriptUnoPlayer::pickAction(UnoGame *game) {
	HandleScope scope;
	Local<Function> pickAction_cb = getCallback("pickAction");

	Handle<Value> picked_index;
	Local<FunctionTemplate> pickActionAfter_cb = FunctionTemplate::New(pickActionAfter);
	Handle<Value> argument = pickActionAfter_cb->GetFunction();

	{   // call pickAction_cb
		TryCatch try_catch;
		picked_index = pickAction_cb->Call(Context::GetCurrent()->Global(), 1, &argument);
		if (try_catch.HasCaught()) {
			node::FatalException(try_catch);
		}
	}

	UnoAction* picked = NULL;

	if (picked_index->IsInt32()) {
		picked = hand[picked_index->Int32Value()];

		std::string message;
		if (game->isValidMove(picked, message) == false) {
			// invalid
		}
	} else {
		// invalid
	}

	/** @todo add color picking */

	return picked;
}

Handle<Value> pickActionAfter(const Arguments &args) {
	REQ_INT_ARG(0);

	int picked_index = args[0]->Int32Value();

	throw picked_index;

	return Undefined();
}

Local<Object> JavascriptUnoPlayer::createCardObject(UnoCard* card) {
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
		value = O; \
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

Local<Object> JavascriptUnoPlayer::createPlayerObject(UnoPlayer* player) {
	HandleScope scope;
	Local<Object> jsplayer = Object::New();

	jsplayer->Set(
		String::NewSymbol("name"),
		String::New(player->getName().c_str())
	);

	return scope.Close(jsplayer);
}

void JavascriptUnoPlayer::notify(EVENT event_type, void* event) {
	HandleScope scope;

	Local<Function> notify_cb = getCallback("notify");

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

	default:
		break;

	}

	jsevent->Set(
			String::NewSymbol("event_type"),
			String::New(jstype)
	);

	Handle<Value> argument = jsevent;

	{   // call notify_cb
		TryCatch try_catch;
		notify_cb->Call(Context::GetCurrent()->Global(), 1, &argument);
		if (try_catch.HasCaught()) {
			node::FatalException(try_catch);
		}
	}
}

#undef REQ_INT_ARG

}}} //namespace
