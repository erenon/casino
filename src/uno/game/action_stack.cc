#include "action_stack.h"

#include "../action/card.h"

#include <stdexcept>
#include <deque>

//shuffle:
#include <algorithm>
#include <ctime>
#include <cstdlib>

namespace Uno { namespace Game {

using ::Uno::Action::Card;

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

void ActionStack::addCard(Card *card) {
	deck.push_back(card);
}

void ActionStack::shuffleDeck() {
	shuffle(deck);
}

void ActionStack::playOutFirstCard() {
	Card* top_card;
	bool card_ok = false;

	while (!card_ok) {
		top_card = drawCard();
		CARD_COLOR color = top_card->getColor();
		CARD_VALUE value = top_card->getValue();

		if (
			color != CARD_COLOR_BLACK
		&&  value != CARD_VALUE_BLOCK
		&&  value != CARD_VALUE_PLUSTWO
		&&  value != CARD_VALUE_REVERSE
		) {
			//card ok, play out
			last_played_color = top_card->getColor();
			last_played_value = top_card->getValue();
			addCardToPlayed(top_card);
			card_ok = true;
		} else {
			//!SimpleCard, take it back
			addCard(top_card);
		}
	}
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

}} //namespace
