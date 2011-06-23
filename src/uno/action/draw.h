#ifndef CSU_DRAW_H_
#define CSU_DRAW_H_

#include "../action/action.h"
#include "../game/game.h"
#include "../../common/player/player.h"

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::UnoAction;
using ::Casino::Uno::Game::UnoGame;
using ::Casino::Common::Player::Player;

class Draw :public UnoAction
{
public:
	bool isDisposeable() {
		return false;
	}

	void takeAction(UnoGame* game) {
		Player *player = game->getCurrentPlayer();

		if (game->isPenality()) {
			game->dealPenality(player);
		} else {
			game->dealCard(player);
		}
	}
};

}}} //namespace

#endif /* CSU_DRAW_H_ */
