#include "action_stack.h"

#include "../action/card.h"

#include <stdexcept>
#include <deque>

//shuffle:
#include <algorithm>
#include <ctime>
#include <cstdlib>

namespace Casino { namespace Uno { namespace Game {

using ::Casino::Uno::Action::Card;

ptrdiff_t ActionStack::getrandom(ptrdiff_t i) {
	return rand() % i;
}

void ActionStack::shuffle(std::deque<Card *> &toShuffle) {
	srand( unsigned( time(NULL)));
 	std::random_shuffle(toShuffle.begin(), toShuffle.end(), getrandom);
}

void ActionStack::shufflePlayedIntoDeck() {
	shuffle(played);

	std::deque<Card *>::iterator it;
	for (it = played.begin(); it != played.end(); it++) {
		addCard(*it);
	}

	played.clear();
}

void ActionStack::shuffleDeck() {
	shuffle(deck);
}

void ActionStack::addCard(Card *card) {
	deck.push_back(card);
}

void ActionStack::addCardToPlayed(Card *card) {
	played.push_front(card);
}

Card* ActionStack::drawCard() {
	if (deck.size() == 0) {
		if (played.size() > 0) {
			shufflePlayedIntoDeck();
		} else {
			throw std::length_error("No card in deck");
		}
	}

	Card* top_card = deck.front();
	deck.pop_front();
	return top_card;
}

}}} //namespace
