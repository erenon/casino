#ifndef TEST_UNO_PLAYER_PLAYER_NOPUREVIRTUAL_H_
#define TEST_UNO_PLAYER_PLAYER_NOPUREVIRTUAL_H_

#include "gmock/gmock.h"

#include "../../../src/uno/player/player.h"
#include "../../../src/uno/event/event.h"

namespace Test { namespace Uno { namespace Player {

using ::Uno::Player::Player;

/**
 * This class is needed becouse of the pure virtual methods of Player.
 *
 * To test Player methods, we have to instantiate this class to
 * give fake implementations to pure virtual methods.
 */
class PlayerNopurevirtual :public Player
{
 public:
	MOCK_METHOD2(notify, void(::Uno::Event::EVENT event_type, void* event));
};

}}}  // namespace

#endif  // TEST_UNO_PLAYER_PLAYER_NOPUREVIRTUAL_H_
