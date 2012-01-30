#ifndef SRC_UNO_NODE_GAME_GAME_WRAPPER_H_
#define SRC_UNO_NODE_GAME_GAME_WRAPPER_H_

#include <nodejs/v8.h>
#include <nodejs/node.h>

#include "../../game/async_game.h"

namespace Uno { namespace Node { namespace Game {

using namespace v8;
//using namespace node;

using ::Uno::Game::AsyncGame;

class GameWrapper {

 public:
    static void Initialize(Handle<Object> target);
    static Handle<Value> New(const Arguments &args);
    static void CleanupGame(Persistent<Value> object, void*);
    static AsyncGame* UnwrapGame(Local<Object> Holder);
    static Handle<Value> JoinPlayer(const Arguments &args);
    static Handle<Value> GetPlayerCount(const Arguments &args);
    static Handle<Value> Start(const Arguments &args);
    static Handle<Value> Dispose(const Arguments &args);

    static void GcEpilogue(GCType type, GCCallbackFlags flags);
};

}}}  // namespace

#endif  // SRC_UNO_NODE_GAME_GAME_WRAPPER_H_
