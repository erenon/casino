#ifndef CTU_PLAYER_CONCRETE_H_
#define CTU_PLAYER_CONCRETE_H_

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

class PlayerConcrete :public Player
{
public:
	MOCK_METHOD1(pickAction, Action*(Game *game));
	MOCK_METHOD2(notify, void(Event::EVENT event_type, void* event));
};

}}}} //namespace

#endif /* CTU_PLAYER_CONCRETE_H_ */
