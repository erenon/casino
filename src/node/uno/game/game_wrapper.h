#ifndef CSNU_GAME_WRAPPER_H_
#define CSNU_GAME_WRAPPER_H_

#include <node/v8.h>
#include <node/node.h>
#include <list>
#include  <stdexcept>

#include "../../../uno/game/game.h"
#include "../../../uno/player/player.h"
#include "../../../uno/action/full_card_deck.h"

namespace Casino { namespace Node { namespace Uno { namespace Game {

using namespace v8;
using namespace node;
using ::Casino::Uno::Game::UnoGame;
using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Action::UnoFullCardDeck;

class GameWrapper
:public ObjectWrap
{
public:
	GameWrapper(int max_player_count);

    static void Initialize(Handle<Object> target);
    static Handle<Value> New( const Arguments &args );
    static Handle<Value> JoinPlayer(const Arguments &args);
    static Handle<Value> AddBot(const Arguments &args);
    static Handle<Value> Start(const Arguments &args);
    static Handle<Value> IsValidMove(const Arguments &args);
    static Handle<Value> Dispose(const Arguments &args);

protected:
    UnoGame* game;
    UnoFullCardDeck* deck;
    std::list<UnoPlayer*> players;
    int bot_count;
};

}}}} //namespace

#endif /* CSNU_GAME_WRAPPER_H_ */
