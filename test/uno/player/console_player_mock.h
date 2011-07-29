#ifndef CTU_CONSOLE_PLAYER_MOCK_H_
#define CTU_CONSOLE_PLAYER_MOCK_H_

#include "gmock/gmock.h"

#include "../../../src/uno/player/console_player.h"
#include "../../../src/uno/action/action.h"
#include "../../../src/uno/event/event.h"

#include <iostream>

namespace Casino { namespace Uno { namespace Game {
	class UnoGame;
}}}; //namespace

namespace Casino { namespace Test { namespace Uno { namespace Player {

using ::Casino::Uno::Player::ConsolePlayer;
using ::Casino::Uno::Action::Action;
using ::Casino::Uno::Game::Game;
namespace Event = ::Casino::Uno::Event;

class ConsolePlayerMock :public ConsolePlayer
{
public:
	ConsolePlayerMock(std::istream& in, std::ostream& out)
		:ConsolePlayer(in, out)
	{}
	MOCK_METHOD1(pickAction, Action*(Game *game));
	MOCK_METHOD2(notify, void(Event::EVENT event_type, void* event));
	void listCards() {
		ConsolePlayer::listCards();
	}
	int chooseCard() {
		return ConsolePlayer::chooseCard();
	}
};

}}}} //namespace

#endif /* CTU_CONSOLE_PLAYER_MOCK_H_ */
