#ifndef CSU_ASYNC_GAME_H_
#define CSU_ASYNC_GAME_H_

#include "game.h"
#include "game_config.h"
#include "../player/player.h"
#include "../action/action.h"

namespace Casino { namespace Uno { namespace Game {

using ::Casino::Uno::Player::Player;
using ::Casino::Uno::Action::Action;

class AsyncGame :public ::Casino::Uno::Game::Game
{
protected:
	/*Player* previous_nonblocked_player;
	void checkUno();
	void registerNonblockedPlayer(Player* player);

	void initStart();
	bool doesPlayerWin(Player* player);*/
	GameConfig config;

public:
	AsyncGame(int max_player_count);
	void start();
	bool isValidMove(Player* player, Action* action, std::string &message);
	void takeAction(Player* player, Action* action);

	void drawCards();
	//virtual void joinPlayer(Player *player);
	/*void addCardToDeck(Card *card);
	bool isPenalty();
	void increasePenality(int addition);
	void dealPenality(Player* player);
	void dealCard(Player* player);

	SimpleCard lastPlayedCard();
	bool isValidMove(Action* action, std::string &message);
	void blockNextPlayer();
	void reverseTurn();
	void drawCards();
	Draw *getDrawAction();
	void setLastColor(CARD_COLOR color);*/
};

}}} //namespace

#endif /* CSU_ASYNC_GAME_H_ */
