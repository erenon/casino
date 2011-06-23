#ifndef CTC_PLAYER_MOCK_H_
#define CTC_PLAYER_MOCK_H_

#include "gmock/gmock.h"

#include "../../../src/common/player/player.h"
#include "../../../src/common/action/action.h"
#include "../../../src/common/game/game.h"

namespace Casino { namespace Common { namespace Game {
	class Game;
}}}; //namespace

namespace Casino { namespace Test { namespace Common { namespace Player {

using ::Casino::Common::Player::Player;
using ::Casino::Common::Action::Action;
using ::Casino::Common::Player::INFO_T;
using ::Casino::Common::Game::Game;

class PlayerMock :public Player
{
public:
	 MOCK_METHOD1(addAction, void(Action *action));
	 MOCK_METHOD1(removeAction, void(Action *action));
	 MOCK_METHOD0(getActionCount, int());
	 MOCK_METHOD1(pickAction, Action*(Game *game));
	 MOCK_METHOD1(info, void(INFO_T type));
};

}}}} //namespace

#endif /* PLAYER_MOCK_H_ */
