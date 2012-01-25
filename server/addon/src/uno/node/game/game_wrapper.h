#ifndef SRC_UNO_NODE_GAME_GAME_WRAPPER_H_
#define SRC_UNO_NODE_GAME_GAME_WRAPPER_H_

#include <node/v8.h>
#include <node/node.h>
#include <list>
#include  <stdexcept>

#include "../../game/async_game.h"
#include "../../player/player.h"

namespace Uno { namespace Node { namespace Game {

using namespace v8;
using namespace node;
using ::Uno::Game::AsyncGame;
using ::Uno::Player::Player;

class GameWrapper :public ObjectWrap {

 public:
    explicit GameWrapper(int max_player_count);

    static void Initialize(Handle<Object> target);
    static Handle<Value> New(const Arguments &args);
    static Handle<Value> JoinPlayer(const Arguments &args);
    static Handle<Value> AddBot(const Arguments &args);
    static Handle<Value> Start(const Arguments &args);
    static Handle<Value> Dispose(const Arguments &args);

 protected:
    AsyncGame* game;
    std::list<Player*> players;
    int bot_count;
};

}}}  // namespace

#endif  // SRC_UNO_NODE_GAME_GAME_WRAPPER_H_
