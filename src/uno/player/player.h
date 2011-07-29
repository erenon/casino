#ifndef CSU_PLAYER_H_
#define CSU_PLAYER_H_

#include "../../common/player/player.h"
#include "../../uno/action/action.h"
#include "../event/event.h"
#include <vector>
#include <string>

namespace Casino { namespace Uno { namespace Game {
	class Game;
}}} //namespace

namespace Casino { namespace Uno { namespace Player {

using ::Casino::Common::Player::Player;
using ::Casino::Uno::Action::Action;
using ::Casino::Uno::Game::Game;
using namespace ::Casino::Uno::Event;
using std::list;

class UnoPlayer
{
protected:
	std::string name;
	std::vector<Action*> hand;
	typedef std::vector<Action*>::iterator card_iterator;
	bool unoFlag;
	bool blocked;
public:
	UnoPlayer();
	UnoPlayer(const char *name);
	virtual void setName(const char *name);
	virtual std::string getName();
	virtual void addAction(Action *action);
	virtual void removeAction(Action *action);
	virtual Action* pickAction(Game *game) = 0;
	virtual void notify(EVENT event_type, void* event) = 0;
	virtual int getCardCount();
	virtual void setUnoFlag(bool value);
	//virtual bool wrongUno();
	virtual bool getUnoFlag();
	virtual bool isBlocked();
	virtual void block();
	virtual void unblock();
	virtual ~UnoPlayer() {};
};

}}} //namespace


#endif /* CSU_PLAYER_H_ */
