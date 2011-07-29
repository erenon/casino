#ifndef CSU_ACTION_H_
#define CSU_ACTION_H_

namespace Casino { namespace Uno { namespace Game {
	class Game;
}}} //namespace

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Game::Game;

class Action //:public Action
{
public:
	virtual bool isDisposeable() = 0;
	virtual void takeAction(Game* game) = 0;
};

}}} //namespace

#endif /* CSU_ACTION_H_ */
