#ifndef CSU_CONSOLE_PLAYER_H_
#define CSU_CONSOLE_PLAYER_H_

#include "player.h"
#include "../action/card.h"
#include "../action/simple_card.h"
#include "../action/wild_card.h"
#include "../event/event.h"
#include <iostream>

namespace Casino { namespace Uno { namespace Game {
	class Game;
}}} //namespace

namespace Casino { namespace Uno { namespace Player {

using ::Casino::Uno::Player::Player;
using ::Casino::Uno::Game::Game;
//Card, SimpleCard, WildCard, CARD_COLOR, CARD_VALUE
using namespace ::Casino::Uno::Action;
namespace Event = ::Casino::Uno::Event;

class ConsolePlayer :public Player
{
protected:
	std::istream& in;
	std::ostream& out;
	virtual void println(const char* str);
	virtual void listCards();
	virtual int chooseCard();
	virtual CARD_COLOR chooseColor();
public:
	ConsolePlayer(std::istream& in, std::ostream& out);
	virtual Action* pickAction(Game *game);
	virtual void notify(Event::EVENT event_type, void* event);
};

}}} //namespace

#endif /* CSU_CONSOLE_PLAYER_H_ */
