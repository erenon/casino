#ifndef CTU_UNDISPOSEABLE_MOCK_H_
#define CTU_UNDISPOSEABLE_MOCK_H_

#include "../../../src/uno/action/action.h"
#include "../../../src/uno/game/game.h"

namespace Casino { namespace Test { namespace Uno { namespace Action {

using ::Casino::Uno::Action::UnoAction;
using ::Casino::Uno::Game::UnoGame;

class UndisposableMock :public UnoAction
{
	bool isDisposeable() {
		return false;
	}

	void takeAction(UnoGame* game) {}
};

}}}} //namespace

#endif /* CTU_UNDISPOSEABLE_MOCK_H_ */
