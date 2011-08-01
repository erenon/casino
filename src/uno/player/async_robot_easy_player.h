#ifndef CSU_ASYNC_ROBOT_EASY_PLAYER_H_
#define CSU_ASYNC_ROBOT_EASY_PLAYER_H_

#include "player.h"
#include "../action/card.h"
#include "../event/event.h"

namespace Casino { namespace Uno { namespace Game {
	class AsyncGame;
	class ConsoleGame;
}}} //namespace

namespace Casino { namespace Uno { namespace Player {

using ::Casino::Uno::Player::Player;
using ::Casino::Uno::Game::AsyncGame;
//Card, CARD_COLOR, CARD_VALUE
using namespace ::Casino::Uno::Action;
namespace Event = ::Casino::Uno::Event;

class AsyncRobotEasyPlayer :public Player
{
public:
	AsyncRobotEasyPlayer();
	virtual void setGame(AsyncGame* game);
	virtual void notify(Event::EVENT event_type, void* event);
	virtual Action* pickAction(ConsoleGame *game) {}

protected:
	AsyncGame* game;

	virtual Action* pickAction();
	virtual CARD_COLOR chooseColor();
	static bool compareCardValue(Card* a, Card* b);
};

}}} //namespace

#endif /* CSU_ASYNC_ROBOT_EASY_PLAYER_H_ */
