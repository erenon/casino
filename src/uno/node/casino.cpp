#include <node/v8.h>
#include <node/node.h>

#include "game/game_wrapper.h"
#include "player/javascript_player_wrapper.h"

using namespace v8;
using namespace node;

extern "C"
void init( Handle<Object> target ) {
    HandleScope scope;

    ::Uno::Node::Game::GameWrapper::Initialize(target);
    ::Uno::Node::Player::JavascriptPlayerWrapper::Initialize(target);
}

//NODE_MODULE(casino, Casino::Node::Uno::Game::GameWrapper::Initialize);
