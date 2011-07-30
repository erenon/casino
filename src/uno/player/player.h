#ifndef CSU_PLAYER_H_
#define CSU_PLAYER_H_

#include "../action/action.h"
#include "../event/event.h"
#include <vector>
#include <string>

namespace Casino { namespace Uno { namespace Game {
	class ConsoleGame;
}}} //namespace

namespace Casino { namespace Uno { namespace Player {

using ::Casino::Uno::Action::Action;
using ::Casino::Uno::Game::ConsoleGame;
using namespace ::Casino::Uno::Event;

class Player
{
protected:
	std::string name;
	std::vector<Action*> hand;
	typedef std::vector<Action*>::iterator card_iterator;
	bool unoFlag;
	bool blocked;
public:
	Player();
	Player(const char *name);
	virtual void setName(const char *name);
	virtual std::string getName();
	virtual void addAction(Action *action);
	virtual void removeAction(Action *action);
	virtual Action* pickAction(ConsoleGame *game) = 0;
	virtual void notify(EVENT event_type, void* event) = 0;
	virtual int getCardCount();
	virtual void setUnoFlag(bool value);
	//virtual bool wrongUno();
	virtual bool getUnoFlag();
	virtual bool isBlocked();
	virtual void block();
	virtual void unblock();
	virtual ~Player() {};
};

}}} //namespace


#endif /* CSU_PLAYER_H_ */
