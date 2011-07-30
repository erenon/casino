#ifndef CSU_CONSOLE_GAME_H_
#define CSU_CONSOLE_GAME_H_

#include "game.h"
#include "../player/player.h"
#include "../action/card.h"
#include "../action/simple_card.h"
#include "../action/action.h"
#include "../action/draw.h"

#include <deque>
#include <list>
#include <string>

namespace Casino { namespace Uno { namespace Game {

using ::Casino::Uno::Player::Player;
using ::Casino::Uno::Action::Action;
//CARD_COLOR/VALUE, Draw, Card, SimpleCard
using namespace ::Casino::Uno::Action;

class ConsoleGame :public ::Casino::Uno::Game::Game
{
protected:
	Player* previous_nonblocked_player;
	void checkUno();
	void registerNonblockedPlayer(Player* player);

	void initStart();
	bool doesPlayerWin(Player* player);


public:
	ConsoleGame(int max_player_count);

	void start();

	SimpleCard lastPlayedCard();
	bool isValidMove(Action* action, std::string &message);
};

}}} //namespace

#endif /* CSU_CONSOLE_GAME_H_ */
