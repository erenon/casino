#ifndef CTU_PLAYER_MOCK_H_
#define CTU_PLAYER_MOCK_H_

#include "gmock/gmock.h"

#include "../../../src/uno/player/player.h"
#include "../../../src/uno/action/action.h"
#include "../../../src/uno/game/game.h"

namespace Casino { namespace Uno { namespace Game {
	class UnoGame;
}}}; //namespace

namespace Casino { namespace Test { namespace Uno { namespace Player {

using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Action::UnoAction;
using ::Casino::Uno::Player::INFO_T;
using ::Casino::Uno::Game::UnoGame;

class UnoPlayerMock :public UnoPlayer
{
public:
	MOCK_METHOD1(addAction, void(UnoAction *action));
	MOCK_METHOD1(removeAction, void(UnoAction *action));
	MOCK_METHOD1(pickAction, UnoAction*(UnoGame *game));
	MOCK_METHOD1(info, void(INFO_T type));
	MOCK_METHOD0(getCardCount, int());
	MOCK_METHOD1(setUnoFlag, void(bool value));
	MOCK_METHOD0(wrongUno, bool());
	MOCK_METHOD0(isBlocked, bool());
	MOCK_METHOD0(block, void());
	MOCK_METHOD0(unblock, void());
};

}}}} //namespace

#endif /* CTU_PLAYER_MOCK_H_ */
