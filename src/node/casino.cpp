#include <node/v8.h>
#include <node/node.h>

#include <cstring> //strlen
#include <cstdlib>

#include "uno/game/game_wrapper.h"

using namespace v8;
using namespace node;

/** @todo remove this */
static Handle<Value> Hello( const Arguments &args ) {
	HandleScope scope;

	const char *str = "Hello from host";

	return String::New(str, strlen(str));
}

extern "C"
void init( Handle<Object> target ) {
    HandleScope scope;

    /** @todo remove this */
    NODE_SET_METHOD(target, "hello", Hello);

    Casino::Node::Uno::Game::GameWrapper::Initialize(target);
}

//NODE_MODULE(casino, Casino::Node::Uno::Game::GameWrapper::Initialize);
