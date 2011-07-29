#ifndef CSU_CONSOLE_ROBOT_EASY_PLAYER_H_
#define CSU_CONSOLE_ROBOT_EASY_PLAYER_H_

#include "player.h"
#include "../event/event.h"

namespace Casino { namespace Uno { namespace Game {
	class Game;
}}} //namespace

namespace Casino { namespace Uno { namespace Player {

using ::Casino::Uno::Player::Player;
using ::Casino::Uno::Game::Game;
//Card, SimpleCard, WildCard, CARD_COLOR, CARD_VALUE
using namespace ::Casino::Uno::Action;

class RobotEasyUnoPlayer :public Player
{
protected:
	//std::ostream& out;
	/*virtual int chooseCard();*/
	virtual CARD_COLOR chooseColor();
	static bool compareCardValue(Card* a, Card* b);
public:
	RobotEasyUnoPlayer(/*std::ostream& out*/);
	virtual Action* pickAction(Game *game);
	virtual void notify(::Casino::Uno::Event::EVENT event_type, void* event) {}
};

}}} //namespace

#endif /* CSU_CONSOLE_ROBOT_EASY_PLAYER_H_ */
