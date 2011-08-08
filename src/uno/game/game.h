#ifndef CSU_GAME_H_
#define CSU_GAME_H_

#include "../../common/game/game.h"
#include "player_list.h"
#include "action_stack.h"
//#include "../action/action.h"
#include "../player/player.h"
#include "../action/card.h"
#include "../action/draw.h"

namespace Casino { namespace Uno { namespace Game {

using ::Casino::Uno::Player::Player;
//CARD_COLOR/VALUE, Draw
using namespace ::Casino::Uno::Action;

class Game :public ::Casino::Common::Game::Game
{
protected:
	PlayerList players;
	ActionStack deck;

	int current_penalty;
	Draw draw_action;

public:
	Game(int max_player_count);

	virtual void joinPlayer(Player *player);

	virtual void addCardToDeck(Card *card);

	virtual bool isPenalty();
	virtual void increasePenality(int addition);
	virtual void dealPenality(Player* player);
	virtual void dealCard(Player* player);

	virtual void blockNextPlayer();
	virtual void reverseTurn();
	virtual void drawCards();
	virtual Draw *getDrawAction();
	virtual void setLastColor(CARD_COLOR color);
};

}}} //namespace

#endif /* CSU_GAME_H_ */
