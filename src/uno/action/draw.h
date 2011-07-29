#ifndef CSU_DRAW_H_
#define CSU_DRAW_H_

#include "../action/action.h"

namespace Casino { namespace Uno { namespace Game {
	class Game;
}}} //namespace

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::Action;
using ::Casino::Uno::Game::Game;

class Draw :public Action
{
public:
	bool isDisposeable();
	void takeAction(Game* game);
};

}}} //namespace

#endif /* CSU_DRAW_H_ */
