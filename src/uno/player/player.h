#ifndef CSU_PLAYER_H_
#define CSU_PLAYER_H_

#include "../../common/player/player.h"
#include "../../uno/action/action.h"
#include "../../uno/game/game.h"
#include <list>

namespace Casino { namespace Uno { namespace Player {

using ::Casino::Common::Player::Player;
using ::Casino::Uno::Action::UnoAction;
using ::Casino::Uno::Game::UnoGame;
using std::list;

enum INFO_T {

};

class UnoPlayer /*:public Player*/
{
protected:
	list<UnoAction*> hand;
public:
	//UnoPlayer();
	virtual void addAction(UnoAction *action);
	virtual void removeAction(UnoAction *action);
	virtual UnoAction* pickAction(UnoGame *game) = 0;
	virtual void info(INFO_T type) = 0;
	virtual int getCardCount();
	virtual ~UnoPlayer() {};
};

}}} //namespace


#endif /* CSU_PLAYER_H_ */
