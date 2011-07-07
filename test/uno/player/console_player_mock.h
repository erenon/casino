#ifndef CTU_CONSOLE_PLAYER_MOCK_H_
#define CTU_CONSOLE_PLAYER_MOCK_H_

#include "gmock/gmock.h"

#include "../../../src/uno/player/console_player.h"
#include "../../../src/uno/action/action.h"

#include <iostream>

namespace Casino { namespace Uno { namespace Game {
	class UnoGame;
}}}; //namespace

namespace Casino { namespace Test { namespace Uno { namespace Player {

using ::Casino::Uno::Player::ConsoleUnoPlayer;
using ::Casino::Uno::Action::UnoAction;
using ::Casino::Uno::Player::INFO_T;
using ::Casino::Uno::Game::UnoGame;

class ConsoleUnoPlayerMock :public ConsoleUnoPlayer
{
public:
	ConsoleUnoPlayerMock(std::istream& in, std::ostream& out)
		:ConsoleUnoPlayer(in, out)
	{}
	MOCK_METHOD1(pickAction, UnoAction*(UnoGame *game));
	MOCK_METHOD1(info, void(INFO_T type));
	void listCards() {
		ConsoleUnoPlayer::listCards();
	}
	int chooseCard() {
		return ConsoleUnoPlayer::chooseCard();
	}
};

}}}} //namespace

#endif /* CTU_CONSOLE_PLAYER_MOCK_H_ */
