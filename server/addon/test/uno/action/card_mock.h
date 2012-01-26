#ifndef TEST_UNO_ACTION_CARD_MOCK_H_
#define TEST_UNO_ACTION_CARD_MOCK_H_

#include "../../../src/uno/action/card.h"
#include "../../../src/uno/game/game.h"

namespace Test { namespace Uno { namespace Action {

using ::Uno::Action::Card;
using ::Uno::Game::Game;

class CardMock :public Card
{
 public:
	MOCK_METHOD0(isDisposeable, bool());
	MOCK_METHOD1(takeAction, void(Game* game));
};

}}}  // namespace

#endif  // TEST_UNO_ACTION_CARD_MOCK_H_
