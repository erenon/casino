#include "game.h"

#include "../../common/game/game.h"
#include "../player/player.h"
#include "../action/card.h"
#include "../action/action.h"
#include "../action/simple_card.h"

#include <algorithm>
#include <stdexcept>
#include <list>
#include <deque>
#include <typeinfo>

namespace Casino { namespace Uno { namespace Game {

using ::Casino::Common::Game::Game;
using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Action::UnoCard;
using ::Casino::Uno::Action::UnoAction;
using ::Casino::Uno::Action::SimpleCard;

UnoGame::UnoGame(int max_player_count)
	:Game(max_player_count),
	 current_penality(0)
{

}

UnoGame::PlayerList::PlayerList()
	:turn_direction_normal(true),
	 prev_player(NULL)
{
	current_player = players.begin();
}

void UnoGame::PlayerList::joinPlayer(UnoPlayer* player) {
	players.push_back(player);
}

void UnoGame::joinPlayer(UnoPlayer *player) {
	if (players.size() >= max_player_count) {
		throw std::overflow_error("Game is full");
	}

	players.joinPlayer(player);
}

int UnoGame::PlayerList::size() {
	return players.size();
}

UnoGame::PlayerList::player_iterator UnoGame::PlayerList::determineNextPlayer() {
	player_iterator next_player = current_player;

	if (turn_direction_normal) {
		next_player++;

		if (next_player == players.end()) {
			// current player is at the end of the list
			// next player is the first player
			next_player = players.begin();
		}
	} else {
		if (next_player == players.begin()) {
			// current player is at the beginning of the list
			// prev player is at the end
			next_player = players.end();
			next_player--;
		} else {
			next_player--;
		}
	}

	return next_player;
}

UnoPlayer *UnoGame::PlayerList::getNextPlayer() {
	return *determineNextPlayer();
}

UnoPlayer *UnoGame::PlayerList::getPreviousPlayer() {
	return prev_player;
}

UnoPlayer *UnoGame::PlayerList::getCurrentPlayer() {
	return *current_player;
}

UnoPlayer *UnoGame::PlayerList::next() {
	prev_player = *current_player;
	current_player = determineNextPlayer();
	return *current_player;
}

void UnoGame::PlayerList::reset() {
	prev_player = NULL;
	current_player = players.begin();
}

void UnoGame::PlayerList::reverseTurn() {
	turn_direction_normal = !turn_direction_normal;
}

void UnoGame::ActionStack::shuffle(std::deque<UnoCard *> toSuffle) {
	std::random_shuffle(toSuffle.begin(), toSuffle.end());
}

void UnoGame::ActionStack::shufflePlayedIntoDeck() {
	// keep last played
	UnoCard *last_played = lastPlayedCard();
	played.pop_front();

	shuffle(played);

	std::deque<UnoCard *>::iterator it;
	for (it = played.begin(); it != played.end(); it++) {
		addCard(*it);
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
	played.push_front(card);
}

UnoCard* UnoGame::ActionStack::drawCard() {
	if (deck.size() == 0) {
		if (played.size() > 1) { //must keep the top card
			shufflePlayedIntoDeck();
		} else {
			throw std::length_error("No card in deck");
		}
	}

	UnoCard* top_card = deck.front();
	deck.pop_front();
	return top_card;
}

UnoCard *UnoGame::ActionStack::lastPlayedCard() {
	return played.front();
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

	{	// play out first card
		UnoCard* top_card;
		// dummy class to compare
		SimpleCard proper_first_card(
			Casino::Uno::Action::CARD_COLOR_RED,
			Casino::Uno::Action::CARD_VALUE_1
		);
		bool card_ok = false;

		while (!card_ok) {
			top_card = deck.drawCard();

			if (typeid(*top_card) != typeid(proper_first_card)) {
				//card ok, play out
				deck.addCardToPlayed(top_card);
				card_ok = true;
			} else {
				//!SimpleCard, take it back
				deck.addCard(top_card);
			}
		}
	}

	std::list<UnoPlayer *>::iterator player;
	for (int card_idx = 0; card_idx < initial_hand_count; card_idx++) {
		players.reset();
		for (int i = 0; i < players.size(); i++, players.next()) {
			players.getCurrentPlayer()->addAction(deck.drawCard());
		}
	}
}

bool UnoGame::doesPlayerWin(UnoPlayer* player) {
	return (player->isBlocked() == false)
		&& (player->getCardCount() == 0);
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

	players.reset();
	UnoPlayer* current_player = players.getCurrentPlayer();
	bool first_move = true;

	while(!doesPlayerWin(current_player)) {
		// check block
		if (current_player->isBlocked()) { // unblock and continue
			current_player->unblock();
		} else {

			// get players action
			UnoAction* pickedAction = current_player->pickAction(this);

			// call actions action
			pickedAction->takeAction(this);

			/** @todo notify about played card */

			// move card from hand to played cards
			if (pickedAction->isDisposeable()) {
				current_player->removeAction(pickedAction);
				deck.addCardToPlayed(static_cast<UnoCard*>(pickedAction));
			}

		}

		// check uno if not the first move of the first turn
		if (!first_move) {
			checkUno(players.getPreviousPlayer());
		} else {
			first_move = false;
		}

		// lets play the next player
		current_player = players.next();
	}

	/** @todo notify about win/game end */
}

UnoCard *UnoGame::lastPlayedCard() {
	return deck.lastPlayedCard();
}

void UnoGame::blockNextPlayer() {
	players.getNextPlayer()->block();
}

void UnoGame::reverseTurn() {
	players.reverseTurn();
}

}}} //namespace
