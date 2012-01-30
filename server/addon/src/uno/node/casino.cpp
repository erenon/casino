#include <nodejs/v8.h>
#include <nodejs/node.h>

#include "./game/game_wrapper.h"

using namespace v8;
using namespace node;

extern "C"
void init(Handle<Object> target) {
    HandleScope scope;

    ::Uno::Node::Game::GameWrapper::Initialize(target);
}
