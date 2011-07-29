#include "player.h"

namespace Casino { namespace Uno { namespace Player {

using ::Casino::Uno::Action::Action;

Player::Player() :name("player"), unoFlag(false), blocked(false) {}

Player::Player(const char *name)
	:unoFlag(false), blocked(false)
{
	setName(name);
}

void Player::setName(const char *name) {
	this->name = name;
}

std::string Player::getName() {
	return name;
}

void Player::addAction(Action *action) {
	hand.push_back(action);
}

void Player::removeAction(Action *action) {
	card_iterator it;

	for (it = hand.begin(); it != hand.end(); it++) {
		if (*it == action) {
			hand.erase(it);
			break;
		}
	}
}

int Player::getCardCount() {
	card_iterator it;
	int count = 0;

	for (it = hand.begin(); it != hand.end(); it++) {
		if ((*it)->isDisposeable()) {
			count++;
		}
	}

	return count;
}

void Player::setUnoFlag(bool value) {
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
/*bool Player::wrongUno() {
	return (
		(getCardCount() == 1 && unoFlag == false)
	||  (getCardCount() != 1 && unoFlag == true)
	);
}*/

bool Player::getUnoFlag() {
	return unoFlag;
}

bool Player::isBlocked() {
	return blocked;
}

void Player::block() {
	blocked = true;
}

void Player::unblock() {
	blocked = false;
}

}}} //namespace
