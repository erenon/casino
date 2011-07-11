#ifndef CTU_PLAYER_CONCRETE_H_
#define CTU_PLAYER_CONCRETE_H_

#include "gmock/gmock.h"

#include "../../../src/uno/player/player.h"
#include "../../../src/uno/action/action.h"
#include "../../../src/uno/game/game.h"
#include "../../../src/uno/event/event.h"

namespace Casino { namespace Uno { namespace Game {
	class UnoGame;
}}}; //namespace

namespace Casino { namespace Test { namespace Uno { namespace Player {

using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Action::UnoAction;
using ::Casino::Uno::Game::UnoGame;
namespace Event = ::Casino::Uno::Event;

class UnoPlayerConcrete :public UnoPlayer
{
public:
	MOCK_METHOD1(pickAction, UnoAction*(UnoGame *game));
	MOCK_METHOD2(notify, void(Event::EVENT event_type, void* event));
};

}}}} //namespace

#endif /* CTU_PLAYER_CONCRETE_H_ */
