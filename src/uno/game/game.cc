#include "game.h"

#include "../../common/game/game.h"
#include "../player/player.h"
#include "../action/card.h"

#include <algorithm>
#include <stdexcept>

namespace Casino { namespace Uno { namespace Game {

using ::Casino::Common::Game::Game;
using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Action::UnoCard;

UnoGame::UnoGame(int max_player_count)
	:Game(max_player_count),
	 current_penality(0)
{

}

void UnoGame::ActionStack::shufflePlayedIntoDeck() {
	std::random_shuffle(played.begin(), played.end());

	std::vector<UnoCard *>::iterator it;

	for (it = played.begin(); it != played.end(); it++) {
		deck.push(*it);
	}

	played.clear();
}
void UnoGame::ActionStack::addCard(UnoCard *card) {
	deck.push(card);
}

UnoCard* UnoGame::ActionStack::drawCard() {
	if (deck.size() == 0) {
		if (played.size() != 0) {
			shufflePlayedIntoDeck();
		} else {
			throw std::length_error("No card in deck");
		}
	}

	UnoCard* top_card = deck.top();
	deck.pop();
	return top_card;
}

void UnoGame::addCardToDeck(UnoCard *card) {
	deck.addCard(card);
}

bool UnoGame::isPenality() {
	return (current_penality > 0);
}

void UnoGame::increasePenality(int addition) {
	current_penality += addition;
}

void UnoGame::dealPenality(UnoPlayer* player) {
	for (int i = 0; i < current_penality; i++) {
		dealCard(player);
	}

	current_penality = 0;
}

void UnoGame::dealCard(UnoPlayer* player) {
	UnoCard* top_card = deck.drawCard();
	player->addAction(top_card);
}

}}} //namespace
