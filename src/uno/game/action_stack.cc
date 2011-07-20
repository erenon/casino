#include "game.h"

#include "../action/card.h"

#include <stdexcept>
#include <deque>

//shuffle:
#include <algorithm>
#include <ctime>
#include <cstdlib>

namespace Casino { namespace Uno { namespace Game {

using ::Casino::Uno::Action::UnoCard;

ptrdiff_t UnoGame::ActionStack::getrandom(ptrdiff_t i) {
	return rand() % i;
}

void UnoGame::ActionStack::shuffle(std::deque<UnoCard *> &toShuffle) {
	srand( unsigned( time(NULL)));
 	std::random_shuffle(toShuffle.begin(), toShuffle.end(), getrandom);
}

void UnoGame::ActionStack::shufflePlayedIntoDeck() {
	shuffle(played);

	std::deque<UnoCard *>::iterator it;
	for (it = played.begin(); it != played.end(); it++) {
		addCard(*it);
	}

	played.clear();
}

void UnoGame::ActionStack::shuffleDeck() {
	shuffle(deck);
}

void UnoGame::ActionStack::addCard(UnoCard *card) {
	deck.push_back(card);
}

void UnoGame::ActionStack::addCardToPlayed(UnoCard *card) {
	played.push_front(card);
}

UnoCard* UnoGame::ActionStack::drawCard() {
	if (deck.size() == 0) {
		if (played.size() > 0) {
			shufflePlayedIntoDeck();
		} else {
			throw std::length_error("No card in deck");
		}
	}

	UnoCard* top_card = deck.front();
	deck.pop_front();
	return top_card;
}

}}} //namespace
