#include "player.h"

//#include "../../common/player/player.h"
//#include "../../common/action/action.h"
#include <list>

namespace Casino { namespace Uno { namespace Player {

using ::Casino::Common::Player::Player;
using ::Casino::Uno::Action::UnoAction;
using std::list;

void UnoPlayer::addAction(UnoAction *action) {
	hand.push_back(action);
}

void UnoPlayer::removeAction(UnoAction *action) {
	hand.remove(action);
}

int UnoPlayer::getCardCount() {
	list<UnoAction*>::iterator it;
	int count = 0;

	for (it = hand.begin(); it != hand.end(); it++) {
		if ((*it)->isDisposeable()) {
			count++;
		}
	}

	return count;
}

}}} //namespace
