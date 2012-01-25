#ifndef CTU_UNDISPOSEABLE_MOCK_H_
#define CTU_UNDISPOSEABLE_MOCK_H_

#include "../../../src/uno/action/action.h"
#include "../../../src/uno/game/game.h"

namespace Casino { namespace Test { namespace Uno { namespace Action {

using ::Casino::Uno::Action::Action;
using ::Casino::Uno::Game::Game;

class UndisposableMock :public Action
{
	bool isDisposeable() {
		return false;
	}

	void takeAction(Game* game) {}
};

}}}} //namespace

#endif /* CTU_UNDISPOSEABLE_MOCK_H_ */
