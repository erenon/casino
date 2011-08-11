#ifndef SRC_UNO_GAME_GAME_H_
#define SRC_UNO_GAME_GAME_H_

#include "./player_list.h"
#include "./deck.h"
#include "../player/player.h"
#include "../action/card.h"
#include "../action/draw.h"

namespace Uno { namespace Game {

using ::Uno::Player::Player;
// CARD_COLOR/VALUE, Draw
using namespace ::Uno::Action;

class Game {

protected:
    int max_player_count;

    PlayerList players;
    Deck deck;

    int current_penalty;
    Draw draw_action;

public:
    Game(int max_player_count);
    virtual ~Game() {};

    virtual void joinPlayer(Player *player);
    virtual int getPlayerCount();

    virtual bool isPenalty();
    virtual void increasePenality(int addition);
    virtual void dealPenality(Player* player);
    virtual void dealCard(Player* player);

    virtual void blockNextPlayer();
    virtual void reverseTurn();
    virtual void drawCards();
    virtual void setLastColor(CARD_COLOR color);
};

}}  // namespace

#endif  // SRC_UNO_GAME_GAME_H_
