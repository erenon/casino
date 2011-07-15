#include <node/v8.h>
#include <node/node.h>
#include <list>
#include <stdexcept>
#include <string>

#include "game_wrapper.h"
#include "../../../uno/game/game.h"
#include "../../../uno/player/player.h"
#include "../../../uno/player/javascript_player.h"
#include "../../../uno/player/robot_easy_player.h"
#include "../../../uno/action/full_card_deck.h"

namespace Casino { namespace Node { namespace Uno { namespace Game {

using namespace v8;
using namespace node;
using ::Casino::Uno::Game::UnoGame;
using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Player::JavascriptUnoPlayer;
using ::Casino::Uno::Player::RobotEasyUnoPlayer;
using ::Casino::Uno::Action::UnoFullCardDeck;

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

GameWrapper::GameWrapper(int max_player_count)
	:bot_count(0)
{
	game = new UnoGame(max_player_count);

	deck = new UnoFullCardDeck();
	deck->fillGameWithCards(game);
}

void GameWrapper::Initialize(Handle<Object> target) {
	HandleScope scope;

	// t is a container
	Local<FunctionTemplate> t = FunctionTemplate::New(New);
	t->InstanceTemplate()->SetInternalFieldCount(1);

	//NODE_SET_METHOD(t, "createGame", CreateGame);
	NODE_SET_PROTOTYPE_METHOD(t, "joinPlayer", JoinPlayer);
	NODE_SET_PROTOTYPE_METHOD(t, "start", Start);
	NODE_SET_PROTOTYPE_METHOD(t, "dispose", Dispose);
	NODE_SET_PROTOTYPE_METHOD(t, "addBot", AddBot);

	target->Set(String::NewSymbol("game"), t->GetFunction());
}

Handle<Value> GameWrapper::New( const Arguments &args ) {
	HandleScope scope;

	REQ_INT_ARG(0);

	GameWrapper* wrapper = new GameWrapper(args[0]->Int32Value());
	wrapper->Wrap(args.This());

	return args.This();
}

/**
 * @todo disallow non-unique session id
 */
Handle<Value> GameWrapper::JoinPlayer(const Arguments &args) {
	HandleScope scope;
	GameWrapper* wrapper = ObjectWrap::Unwrap<GameWrapper>(args.This());

	REQ_OBJ_ARG(0);

	JavascriptUnoPlayer* player = new JavascriptUnoPlayer(
		args[0]->ToObject()
	);

	try {
		wrapper->game->joinPlayer(player);
		wrapper->players.push_back(player);
	} catch (std::overflow_error e) {
		delete player;

		return ThrowException(Exception::RangeError(
			String::New("Game is full")
		));
	}

	return scope.Close(Boolean::New(true));
}

Handle<Value> GameWrapper::AddBot(const Arguments &args) {
	int count;
	if (args.Length() >= 1 && args[0]->IsInt32()) {
		count = args[0]->Int32Value();
	} else {
		count = 1;
	}

	HandleScope scope;
	GameWrapper* wrapper = ObjectWrap::Unwrap<GameWrapper>(args.This());
	for (int i = 0; i < count; i++) {
		RobotEasyUnoPlayer *robot = new RobotEasyUnoPlayer();

		{ // hack ahead. 49: ASCII 0
			std::string name = "robot ";
			name.push_back((char)(wrapper->bot_count+49));
			robot->setName(name.c_str());
		}

		try {
			wrapper->game->joinPlayer(robot);
			wrapper->players.push_back(robot);
			wrapper->bot_count++;
		} catch (std::overflow_error e) {
			delete robot;

			return ThrowException(Exception::RangeError(
				String::New("Game is full")
			));
		}
	}

	return scope.Close(Boolean::New(true));
}

Handle<Value> GameWrapper::Start(const Arguments &args) {
	HandleScope scope;
	GameWrapper* wrapper = ObjectWrap::Unwrap<GameWrapper>(args.This());

	wrapper->game->start();

	return scope.Close(Boolean::New(true));
}

Handle<Value> GameWrapper::Dispose(const Arguments &args) {
	HandleScope scope;
	GameWrapper* wrapper = ObjectWrap::Unwrap<GameWrapper>(args.This());

	delete wrapper->game;
	delete wrapper->deck;

	std::list<UnoPlayer*>::iterator player;
	for (player = wrapper->players.begin(); player != wrapper->players.end(); player++) {
		delete (*player);
	}

	return scope.Close(Undefined());
}

}}}} //namespace
