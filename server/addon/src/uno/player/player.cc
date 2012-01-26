#include "./player.h"

namespace Uno { namespace Player {

using ::Uno::Action::Action;

Player::Player() :name("player"), unoFlag(false), blocked(false) {}

Player::Player(const char *name) :unoFlag(false), blocked(false) {
    setName(name);
}

void Player::setName(const char *name) {
    this->name = name;
}

std::string Player::getName() {
    return name;
}

void Player::addCard(Card *card) {
    hand.push_back(card);
}

void Player::removeCard(Card *card) {
    card_iterator it;

    for (it = hand.begin(); it != hand.end(); it++) {
        if (*it == card) {
            hand.erase(it);
            break;
        }
    }
}

int Player::getCardCount() {
	return hand.size();
}

void Player::setUnoFlag(bool value) {
    unoFlag = value;
}

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

}}  // namespace
