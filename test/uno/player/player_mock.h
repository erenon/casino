#ifndef CTU_PLAYER_MOCK_H_
#define CTU_PLAYER_MOCK_H_

#include "gmock/gmock.h"

#include "../../../src/uno/player/player.h"
#include "../../../src/uno/action/action.h"
#include "../../../src/uno/game/game.h"
#include "../../../src/uno/event/event.h"

namespace Casino { namespace Uno { namespace Game {
	class Game;
}}}; //namespace

namespace Casino { namespace Test { namespace Uno { namespace Player {

using ::Casino::Uno::Player::Player;
using ::Casino::Uno::Action::Action;
using ::Casino::Uno::Game::Game;
namespace Event = ::Casino::Uno::Event;

class PlayerMock :public Player
{
public:
	MOCK_METHOD1(addAction, void(Action *action));
	MOCK_METHOD1(removeAction, void(Action *action));
	MOCK_METHOD1(pickAction, Action*(Game *game));
	MOCK_METHOD2(notify, void(Event::EVENT event_type, void* event));
	MOCK_METHOD0(getCardCount, int());
	MOCK_METHOD1(setUnoFlag, void(bool value));
	//MOCK_METHOD0(wrongUno, bool());
	MOCK_METHOD0(getUnoFlag, bool());
	MOCK_METHOD0(isBlocked, bool());
	MOCK_METHOD0(block, void());
	MOCK_METHOD0(unblock, void());
};

}}}} //namespace

#endif /* CTU_PLAYER_MOCK_H_ */
