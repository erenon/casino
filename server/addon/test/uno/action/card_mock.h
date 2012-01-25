#ifndef CTU_CARD_MOCK_H_
#define CTU_CARD_MOCK_H_

#include "gmock/gmock.h"

#include "../../../src/uno/action/card.h"
#include "../../../src/uno/game/game.h"

namespace Casino { namespace Test { namespace Uno { namespace Action {

using ::Casino::Uno::Action::Card;
using ::Casino::Uno::Game::Game;

class CardMock :public Card
{
public:
	MOCK_METHOD0(isDisposeable, bool());
	MOCK_METHOD1(takeAction, void(Game* game));
};

}}}} //namespace

#endif /* CTU_CARD_MOCK_H_ */
