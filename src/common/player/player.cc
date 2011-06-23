#include "player.h"
#include "../action/action.h"

namespace Casino { namespace Common { namespace Player {

using ::Casino::Common::Action::Action;

void Player::addAction(Action *action) {
	hand.push_back(action);
}

void Player::removeAction(Action *action) {
	hand.remove(action);
}

int Player::getActionCount() {
	return hand.size();
}

}}};
