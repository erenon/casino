#ifndef SRC_UNO_NODE_PLAYER_JAVASCRIPT_PLAYER_WRAPPER_H_
#define SRC_UNO_NODE_PLAYER_JAVASCRIPT_PLAYER_WRAPPER_H_

#include <node/v8.h>
#include <node/node.h>

#include "../../player/async_player.h"

namespace Uno { namespace Node { namespace Player {

using namespace v8;
using namespace node;
using ::Uno::Player::AsyncPlayer;

class JavascriptPlayerWrapper :public ObjectWrap {

public:
    static void Initialize(Handle<Object> target);
    static Handle<Value> New(const Arguments &args);
    static Handle<Value> PlayCard(const Arguments &args);
    static Handle<Value> Draw(const Arguments &args);
    static Handle<Value> Dispose(const Arguments &args);

    AsyncPlayer* getNativePlayer();
    ~JavascriptPlayerWrapper();

protected:
    AsyncPlayer* player;

    explicit JavascriptPlayerWrapper(Handle<Object> jsplayer);
};

}}}  // namespace

#endif  // SRC_UNO_NODE_PLAYER_JAVASCRIPT_PLAYER_WRAPPER_H_
