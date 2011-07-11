#ifndef CSU_CONSOLE_ROBOT_EASY_PLAYER_H_
#define CSU_CONSOLE_ROBOT_EASY_PLAYER_H_

#include "player.h"
#include "../event/event.h"

namespace Casino { namespace Uno { namespace Game {
	class UnoGame;
}}} //namespace

namespace Casino { namespace Uno { namespace Player {

using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Game::UnoGame;
//UnoCard, SimpleCard, WildCard, CARD_COLOR, CARD_VALUE
using namespace ::Casino::Uno::Action;

class RobotEasyUnoPlayer :public UnoPlayer
{
protected:
	//std::ostream& out;
	/*virtual int chooseCard();*/
	virtual CARD_COLOR chooseColor();
	static bool compareCardValue(UnoCard* a, UnoCard* b);
public:
	RobotEasyUnoPlayer(/*std::ostream& out*/);
	virtual UnoAction* pickAction(UnoGame *game);
	virtual void notify(::Casino::Uno::Event::EVENT event_type, void* event) {}
};

}}} //namespace

#endif /* CSU_CONSOLE_ROBOT_EASY_PLAYER_H_ */
