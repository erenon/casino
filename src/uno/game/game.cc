#include "game.h"

#include "../../common/game/game.h"
#include "../player/player.h"
#include "../action/card.h"
#include "../action/action.h"

#include <algorithm>
#include <stdexcept>
#include <list>

namespace Casino { namespace Uno { namespace Game {

using ::Casino::Common::Game::Game;
using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Action::UnoCard;
using ::Casino::Uno::Action::UnoAction;

UnoGame::UnoGame(int max_player_count)
	:Game(max_player_count),
	 current_penality(0),
	 turn_direction_normal(true)
{

}

void UnoGame::joinPlayer(UnoPlayer *player) {
	if (getPlayerCount() >= max_player_count) {
		throw std::overflow_error("Game is full");
	}

	players.push_back(player);
}

void UnoGame::ActionStack::shuffle(std::vector<UnoCard *> toSuffle) {
	std::random_shuffle(toSuffle.begin(), toSuffle.end());
}

void UnoGame::ActionStack::shufflePlayedIntoDeck() {
	// keep last played
	UnoCard *last_played = lastPlayedCard();
	played.pop_back();


	shuffle(played);

	std::vector<UnoCard *>::iterator it;
	for (it = played.begin(); it != played.end(); it++) {
		deck.push_back(*it);
	}

	played.clear();
	addCardToPlayed(last_played);
}

void UnoGame::ActionStack::shuffleDeck() {
	shuffle(deck);
}

void UnoGame::ActionStack::addCard(UnoCard *card) {
	deck.push_back(card);
}

void UnoGame::ActionStack::addCardToPlayed(UnoCard *card) {
	played.push_back(card);
}

UnoCard* UnoGame::ActionStack::drawCard() {
	if (deck.size() == 0) {
		if (played.size() > 1) { //must keep the top card
			shufflePlayedIntoDeck();
		} else {
			throw std::length_error("No card in deck");
		}
	}

	UnoCard* top_card = deck.back();
	deck.pop_back();
	return top_card;
}

UnoCard *UnoGame::ActionStack::lastPlayedCard() {
	return played.back();
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

/**
 * Shuffle cards and deal initial hands
 */
void UnoGame::initStart() {
	const int initial_hand_count = 7;

	deck.shuffleDeck();

	/** @todo should play out the first card */

	std::list<UnoPlayer *>::iterator player;
	for (int card_idx = 0; card_idx < initial_hand_count; card_idx++) {
		for (player = players.begin(); player != players.end(); player++) {
			(*player)->addAction(deck.drawCard());
		}
	}
}

bool UnoGame::doesPlayerWin(UnoPlayer* player) {
	return (player->getCardCount() == 0);
}

UnoGame::player_iterator UnoGame::getPreviousPlayer() {
	if (turn_direction_normal) {
		return current_player--;
	} else {
		return current_player++;
	}
}

UnoGame::player_iterator UnoGame::getNextPlayer() {
	if (turn_direction_normal) {
		return current_player++;
	} else {
		return current_player--;
	}
}

void UnoGame::checkUno(UnoPlayer* player) {
	if (player->wrongUno()) {
		dealCard(player);
		dealCard(player);
	}

	player->setUnoFlag(false);
}

void UnoGame::start() {
	initStart();

	current_player = players.begin();

	while(!doesPlayerWin(*current_player)) {
		// check block
		if ((*current_player)->isBlocked()) { // unblock and continue
			(*current_player)->unblock();
			continue;
		}

		// get players action
		UnoAction* pickedAction = (*current_player)->pickAction(this);

		// call actions action
		pickedAction->takeAction(this);

		/** @todo notify about played card */

		// move card from hand to played cards
		if (pickedAction->isDisposeable()) {
			(*current_player)->removeAction(pickedAction);
			deck.addCardToPlayed(static_cast<UnoCard*>(pickedAction));
		}

		checkUno(*getPreviousPlayer());

		// lets play the next player
		current_player = getNextPlayer();
	}

	/** @todo notify about win/game end */
}

UnoCard *UnoGame::lastPlayedCard() {
	return deck.lastPlayedCard();
}

void UnoGame::blockNextPlayer() {
	(*getNextPlayer())->block();
}

void UnoGame::reverseTurn() {
	turn_direction_normal = !turn_direction_normal;
}

}}} //namespace
