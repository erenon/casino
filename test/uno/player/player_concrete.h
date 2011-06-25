#ifndef CTU_PLAYER_CONCRETE_H_
#define CTU_PLAYER_CONCRETE_H_

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

class UnoPlayerConcrete :public UnoPlayer
{
public:
	MOCK_METHOD1(pickAction, UnoAction*(UnoGame *game));
	MOCK_METHOD1(info, void(INFO_T type));
};

}}}} //namespace

#endif /* CTU_PLAYER_CONCRETE_H_ */
