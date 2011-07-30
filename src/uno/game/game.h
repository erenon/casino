#ifndef CSU_GAME_H_
#define CSU_GAME_H_

#include "../../common/game/game.h"
#include "../player/player.h"
#include "../action/card.h"
#include "../action/simple_card.h"
#include "../action/action.h"
#include "../action/draw.h"
#include "player_list.h"
#include "action_stack.h"

#include <deque>
#include <list>
#include <string>

namespace Casino { namespace Uno { namespace Game {

using ::Casino::Uno::Player::Player;
using ::Casino::Uno::Action::Action;
//CARD_COLOR/VALUE, Draw, Card, SimpleCard
using namespace ::Casino::Uno::Action;

class Game :public ::Casino::Common::Game::Game
{
protected:
	PlayerList players;
	ActionStack deck;

	int current_penalty;
	Draw draw_action;

	Player* previous_nonblocked_player;
	void checkUno();
	void registerNonblockedPlayer(Player* player);

	void initStart();
	bool doesPlayerWin(Player* player);


public:
	Game(int max_player_count);
	virtual void joinPlayer(Player *player);
	void addCardToDeck(Card *card);
	bool isPenalty();
	void increasePenality(int addition);
	void dealPenality(Player* player);
	void dealCard(Player* player);

	void start();

	SimpleCard lastPlayedCard();
	bool isValidMove(Action* action, std::string &message);
	void blockNextPlayer();
	void reverseTurn();
	void drawCards();
	Draw *getDrawAction();
	void setLastColor(CARD_COLOR color);
};

}}} //namespace

#endif /* CSU_GAME_H_ */
