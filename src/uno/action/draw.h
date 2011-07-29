#ifndef CSU_DRAW_H_
#define CSU_DRAW_H_

#include "../action/action.h"

namespace Casino { namespace Uno { namespace Game {
	class UnoGame;
}}} //namespace

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::Action;
using ::Casino::Uno::Game::UnoGame;

class Draw :public Action
{
public:
	bool isDisposeable();
	void takeAction(UnoGame* game);
};

}}} //namespace

#endif /* CSU_DRAW_H_ */
