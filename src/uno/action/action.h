#ifndef CSU_ACTION_H_
#define CSU_ACTION_H_

#include "../../common/action/action.h"
#include "../game/game.h"

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Common::Action::Action;
using ::Casino::Uno::Game::UnoGame;

class UnoAction :public Action
{
public:
	virtual bool isDisposeable() = 0;
	virtual void takeAction(UnoGame* game) = 0;
};

}}} //namespace

#endif /* CSU_ACTION_H_ */
