#include <node/v8.h>
#include <node/node.h>
#include <list>
#include <stdexcept>
#include <string>

#include "game_wrapper.h"
#include "../player/javascript_player_wrapper.h"
#include "../../../uno/player/javascript_player.h"
#include "../../../uno/player/async_robot_easy_player.h"
#include "../../../uno/action/full_card_deck.h"

namespace Casino { namespace Node { namespace Uno { namespace Game {

using namespace v8;
using namespace node;
using ::Casino::Node::Uno::Player::JavascriptPlayerWrapper;
using ::Casino::Node::Uno::Player::JavascriptPlayer;
using ::Casino::Uno::Player::AsyncRobotEasyPlayer;
using ::Casino::Uno::Action::FullCardDeck;

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
	game = new AsyncGame(max_player_count);

	deck = new FullCardDeck();
	deck->fillGameWithCards(game);
}

void GameWrapper::Initialize(Handle<Object> target) {
	HandleScope scope;

	// t is a container
	Local<FunctionTemplate> t = FunctionTemplate::New(New);
	t->InstanceTemplate()->SetInternalFieldCount(1);

	NODE_SET_PROTOTYPE_METHOD(t, "joinPlayer", JoinPlayer);
	NODE_SET_PROTOTYPE_METHOD(t, "addBot", AddBot);
	NODE_SET_PROTOTYPE_METHOD(t, "start", Start);
	NODE_SET_PROTOTYPE_METHOD(t, "dispose", Dispose);

	target->Set(String::NewSymbol("Game"), t->GetFunction());
}

Handle<Value> GameWrapper::New(const Arguments &args) {
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

	Handle<Object> jsplayer_wrapper = args[0]->ToObject()->Get(String::New("native_player"))->ToObject();
	JavascriptPlayerWrapper* player_wrapper = ObjectWrap::Unwrap<JavascriptPlayerWrapper>(jsplayer_wrapper);
	JavascriptPlayer* player = player_wrapper->getNativePlayer();

	/*JavascriptPlayerWrapper* player = new JavascriptPlayerWrapper(
		args[0]->ToObject()
	);*/

	try {
		wrapper->game->joinPlayer(player);
		player->setGame(wrapper->game);
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
		AsyncRobotEasyPlayer *robot = new AsyncRobotEasyPlayer();

		{ // hack ahead. 49: ASCII 0
			std::string name = "robot ";
			name.push_back((char)(wrapper->bot_count+49));
			robot->setName(name.c_str());
		}

		try {
			wrapper->game->joinPlayer(robot);
			robot->setGame(wrapper->game);
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

	std::list<Player*>::iterator player;
	for (player = wrapper->players.begin(); player != wrapper->players.end(); player++) {
		delete (*player);
	}

	return scope.Close(Undefined());
}

#undef REQ_INT_ARG
#undef REQ_OBJ_ARG

}}}} //namespace
