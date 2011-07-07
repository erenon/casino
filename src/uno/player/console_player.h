#ifndef CSU_CONSOLE_PLAYER_H_
#define CSU_CONSOLE_PLAYER_H_

#include "player.h"
#include <iostream>

namespace Casino { namespace Uno { namespace Game {
	class UnoGame;
}}} //namespace

namespace Casino { namespace Uno { namespace Player {

using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Game::UnoGame;

class ConsoleUnoPlayer :public UnoPlayer
{
protected:
	std::istream& in;
	std::ostream& out;
	virtual void println(const char* str);
	virtual void listCards();
	virtual int chooseCard();
public:
	ConsoleUnoPlayer(std::istream& in, std::ostream& out);
	virtual UnoAction* pickAction(UnoGame *game);
	virtual void info(INFO_T type);
};

}}} //namespace

#endif /* CSU_CONSOLE_PLAYER_H_ */
