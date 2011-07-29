#ifndef CSU_CONSOLE_PLAYER_H_
#define CSU_CONSOLE_PLAYER_H_

#include "player.h"
#include "../action/card.h"
#include "../action/simple_card.h"
#include "../action/wild_card.h"
#include "../event/event.h"
#include <iostream>

namespace Casino { namespace Uno { namespace Game {
	class UnoGame;
}}} //namespace

namespace Casino { namespace Uno { namespace Player {

using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Game::UnoGame;
//UnoCard, SimpleCard, WildCard, CARD_COLOR, CARD_VALUE
using namespace ::Casino::Uno::Action;
namespace Event = ::Casino::Uno::Event;

class ConsoleUnoPlayer :public UnoPlayer
{
protected:
	std::istream& in;
	std::ostream& out;
	virtual void println(const char* str);
	virtual void listCards();
	virtual int chooseCard();
	virtual CARD_COLOR chooseColor();
public:
	ConsoleUnoPlayer(std::istream& in, std::ostream& out);
	virtual Action* pickAction(UnoGame *game);
	virtual void notify(Event::EVENT event_type, void* event);
};

}}} //namespace

#endif /* CSU_CONSOLE_PLAYER_H_ */
