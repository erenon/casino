#include "player.h"

//#include "../../common/player/player.h"
//#include "../../common/action/action.h"
#include <list>

namespace Casino { namespace Uno { namespace Player {

using ::Casino::Common::Player::Player;
using ::Casino::Uno::Action::UnoAction;
using std::list;

UnoPlayer::UnoPlayer() :name("player"), unoFlag(false), blocked(false) {}

UnoPlayer::UnoPlayer(const char *name)
	:unoFlag(false), blocked(false)
{
	setName(name);
}

void UnoPlayer::setName(const char *name) {
	this->name = name;
}

std::string UnoPlayer::getName() {
	return name;
}

void UnoPlayer::addAction(UnoAction *action) {
	hand.push_back(action);
}

void UnoPlayer::removeAction(UnoAction *action) {
	card_iterator it;

	for (it = hand.begin(); it != hand.end(); it++) {
		if (*it == action) {
			hand.erase(it);
			break;
		}
	}
}

int UnoPlayer::getCardCount() {
	card_iterator it;
	int count = 0;

	for (it = hand.begin(); it != hand.end(); it++) {
		if ((*it)->isDisposeable()) {
			count++;
		}
	}

	return count;
}

void UnoPlayer::setUnoFlag(bool value) {
	unoFlag = value;
}

/**
 * wrongUno = didForgetUno || fakeUno
 *
 * Checks whether player forgot to say uno,
 * or said uno unnecessarily.
 *
 * @return true, if player should be punished
 */
/*bool UnoPlayer::wrongUno() {
	return (
		(getCardCount() == 1 && unoFlag == false)
	||  (getCardCount() != 1 && unoFlag == true)
	);
}*/

bool UnoPlayer::getUnoFlag() {
	return unoFlag;
}

bool UnoPlayer::isBlocked() {
	return blocked;
}

void UnoPlayer::block() {
	blocked = true;
}

void UnoPlayer::unblock() {
	blocked = false;
}

}}} //namespace
