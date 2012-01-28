#ifndef TEST_UNO_PLAYER_PLAYER_MOCK_H_
#define TEST_UNO_PLAYER_PLAYER_MOCK_H_

#include <string>

#include "gmock/gmock.h"

#include "../../../src/uno/player/player.h"
#include "../../../src/uno/action/card.h"
#include "../../../src/uno/event/event.h"

namespace Test { namespace Uno { namespace Player {

using ::Uno::Player::Player;
using ::Uno::Action::Card;

class PlayerMock :public Player
{
 public:
	MOCK_METHOD1(setName, void(const char* name));
	MOCK_METHOD0(getName, std::string());
	MOCK_METHOD1(addCard, void(Card *card));
	MOCK_METHOD1(removeCard, void(Card *card));
	MOCK_METHOD2(notify, void(::Uno::Event::EVENT event_type, void* event));
	MOCK_METHOD0(getCardCount, int());
	MOCK_METHOD1(setUnoFlag, void(bool value));
	MOCK_METHOD0(getUnoFlag, bool());
	MOCK_METHOD0(isBlocked, bool());
	MOCK_METHOD0(block, void());
	MOCK_METHOD0(unblock, void());
};

}}}  // namespace

#endif  // TEST_UNO_PLAYER_PLAYER_MOCK_H_
