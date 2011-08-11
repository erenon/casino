#ifndef SRC_UNO_PLAYER_ASYNC_PLAYER_H_
#define SRC_UNO_PLAYER_ASYNC_PLAYER_H_

#include <node/v8.h>
#include <node/node.h>
#include <string>

#include "./player.h"
#include "../action/card.h"
#include "../event/event.h"


namespace Uno { namespace Game {
    class AsyncGame;
}}  // namespace

namespace Uno { namespace Player {

using namespace v8;
using ::Uno::Player::Player;
using ::Uno::Action::Card;
using ::Uno::Game::AsyncGame;
namespace Event = ::Uno::Event;

class AsyncPlayer :public Player {

public:
    explicit AsyncPlayer(Handle<Object> jsplayer);
    virtual void setGame(AsyncGame* game);
    virtual Local<Function> getCallback(const char* cbname);
    virtual void addCard(Card *action);
    void playCard(const Arguments &args);
    void draw();
    virtual Local<Object> createCardObject(Card* card);
    virtual Local<Object> createPlayerObject(Player* player);
    virtual void notify(Event::EVENT event_type, void* event);

protected:
    std::string session_id;    /**< to ensure unique players (not implemented) */
    Persistent<Object> jsplayer;
    AsyncGame* game;
};

}}  // namespace

#endif  // SRC_UNO_PLAYER_ASYNC_PLAYER_H_
