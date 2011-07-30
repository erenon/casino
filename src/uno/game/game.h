#ifndef CSU_GAME_H_
#define CSU_GAME_H_

#include "../../common/game/game.h"
#include "player_list.h"
#include "action_stack.h"
#include "../action/action.h"
#include "../action/draw.h"

namespace Casino { namespace Uno { namespace Game {

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

	void addCardToDeck(Card *card);

	bool isPenalty();
	void increasePenality(int addition);
	void dealPenality(Player* player);
	void dealCard(Player* player);

	void blockNextPlayer();
	void reverseTurn();
	void drawCards();
	Draw *getDrawAction();
	void setLastColor(CARD_COLOR color);
};

}}} //namespace

#endif /* CSU_GAME_H_ */
