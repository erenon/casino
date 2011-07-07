#ifndef CSC_PLAYER_H_
#define CSC_PLAYER_H_

#include "../action/action.h"
//#include "../game/game.h"
#include <list>

namespace Casino { namespace Common { namespace Game {
	class Game;
}}}; //namespace

namespace Casino { namespace Common { namespace Player {

using ::Casino::Common::Action::Action;
using ::Casino::Common::Game::Game;
using std::list;

enum INFO_T {

};

class Player
{
protected:
	list<Action*> hand;
public:
	virtual void addAction(Action *action);
	virtual void removeAction(Action *action);
	virtual int getActionCount();
	virtual Action* pickAction(class Game *game) = 0;
	virtual void info(INFO_T type) = 0;
	virtual ~Player() {};

};

}}} //namespace
#endif /* CSC_PLAYER_H_ */
