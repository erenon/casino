#ifndef CSU_PLAYER_H_
#define CSU_PLAYER_H_

#include "../../common/player/player.h"
#include "../../uno/action/action.h"
//#include "../../uno/game/game.h"
#include <list>

namespace Casino { namespace Uno { namespace Game {
	class UnoGame;
}}} //namespace

namespace Casino { namespace Uno { namespace Player {

using ::Casino::Common::Player::Player;
using ::Casino::Uno::Action::UnoAction;
using ::Casino::Uno::Game::UnoGame;
using std::list;

enum INFO_T {

};

class UnoPlayer
{
protected:
	list<UnoAction*> hand;
	bool unoFlag;
	bool blocked;
public:
	UnoPlayer();
	virtual void addAction(UnoAction *action);
	virtual void removeAction(UnoAction *action);
	virtual UnoAction* pickAction(UnoGame *game) = 0;
	virtual void info(INFO_T type) = 0;
	virtual int getCardCount();
	virtual void setUnoFlag(bool value);
	virtual bool wrongUno();
	virtual bool isBlocked();
	virtual void block();
	virtual void unblock();
	virtual ~UnoPlayer() {};
};

}}} //namespace


#endif /* CSU_PLAYER_H_ */
