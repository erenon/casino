#ifndef UNO_PLAYER_PLAYER_H_
#define UNO_PLAYER_PLAYER_H_

#include "../action/action.h"
#include "../event/event.h"
#include <vector>
#include <string>

namespace Uno { namespace Game {
	class Game;
}} //namespace

namespace Uno { namespace Player {

using ::Uno::Action::Action;
namespace Event = ::Uno::Event;

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

	virtual void notify(Event::EVENT event_type, void* event) = 0;
	virtual int getCardCount();
	virtual void setUnoFlag(bool value);
	virtual bool getUnoFlag();
	virtual bool isBlocked();
	virtual void block();
	virtual void unblock();
	virtual ~Player() {};
};

}} //namespace


#endif /* UNO_PLAYER_PLAYER_H_ */
