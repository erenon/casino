#ifndef CTU_DISPOSEABLE_MOCK_H_
#define CTU_DISPOSEABLE_MOCK_H_

#include "../../../src/uno/action/action.h"
#include "../../../src/uno/game/game.h"

namespace Casino { namespace Test { namespace Uno { namespace Action {

using ::Casino::Uno::Action::Action;
using ::Casino::Uno::Game::Game;

class DisposableMock :public Action
{
	bool isDisposeable() {
		return true;
	}

	void takeAction(Game* game) {}
};

}}}} //namespace

#endif /* CTU_DISPOSEABLE_MOCK_H_ */
