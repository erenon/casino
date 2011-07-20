#include "game.h"

#include "../player/player.h"
#include "../action/card.h"
#include "../action/action.h"
#include "../action/simple_card.h"

#include <stdexcept>
#include <typeinfo>

namespace Casino { namespace Uno { namespace Game {

using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Action::UnoCard;
using namespace ::Casino::Uno::Action;	//UnoAction, CARD_COLOR/VALUE
using ::Casino::Uno::Action::SimpleCard;

UnoGame::UnoGame(int max_player_count)
	:Game(max_player_count),
	 current_penality(0),
	 previous_nonblocked_player(NULL)
{

}

void UnoGame::joinPlayer(UnoPlayer *player) {
	if (players.size() >= max_player_count) {
		throw std::overflow_error("Game is full");
	}

	players.joinPlayer(player);


	{ //notify about joined player
		Event::player_joined event;
		event.player = player;
		players.notifyOthers(
			Event::EVENT_PLAYER_JOINED,
			reinterpret_cast<void*>(&event),
			player
		);
	}
}

void UnoGame::checkUno() {
	//no previous player was registered, it's the first move
	if (previous_nonblocked_player == NULL) {
		return;
	}

	UnoPlayer* player = previous_nonblocked_player;

	bool should_say = (player->getCardCount() == 1);
	bool said = player->getUnoFlag();

	if (should_say != said) {
		dealCard(player);
		dealCard(player);
	}

	if (should_say || said) {
		Event::uno_said event;
		event.said_by = player;

		if (should_say == true && said == true) {
			event.type = Event::uno_said::GOOD;
		} else if (should_say == false && said == true) {
			event.type = Event::uno_said::BAD;
		} else if (should_say == true && said == false) {
			event.type = Event::uno_said::FORGOTTEN;
		}

		players.notifyAll(
			Event::EVENT_UNO_SAID,
			reinterpret_cast<void*>(&event)
		);
	}

	if (said) {
		player->setUnoFlag(false);
	}
}

void UnoGame::registerNonblockedPlayer(UnoPlayer* player) {
	previous_nonblocked_player = player;
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

			if (typeid(*top_card) == typeid(proper_first_card)) {
				//card ok, play out
				deck.last_played_color = top_card->getColor();
				deck.last_played_value = top_card->getValue();
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
		&& (player->getCardCount() == 0)
		&& (isPenality() == false);
}

void UnoGame::start() {
	initStart();

	{
		Event::game_start event;
		SimpleCard first_card = lastPlayedCard();
		event.first_card = &first_card;
		players.notifyAll(
			Event::EVENT_GAME_START,
			reinterpret_cast<void*>(&event)
		);
	}

	players.reset();
	UnoPlayer* current_player = players.getCurrentPlayer();
	//bool first_move = true;

	while(!doesPlayerWin(current_player)) {
		// check block
		if (current_player->isBlocked()) { // unblock and continue
			current_player->unblock();
		} else {

			// get players action
			UnoAction* pickedAction = current_player->pickAction(this);

			// move card from hand to played cards
			if (pickedAction->isDisposeable()) {
				current_player->removeAction(pickedAction);

				UnoCard* played_card = static_cast<UnoCard*>(pickedAction);
				deck.last_played_color = played_card->getColor();
				deck.last_played_value = played_card->getValue();
				deck.addCardToPlayed(played_card);

				{ //notify about played card
					Event::card_played event;
					SimpleCard played_card = lastPlayedCard();
					event.played_card = &played_card;
					event.played_by = current_player;
					players.notifyOthers(
						Event::EVENT_CARD_PLAYED,
						reinterpret_cast<void*>(&event),
						current_player
					);
				}
			} else {
				//it's a draw
				//player draws the current penality or a single card
				int card_count = (isPenality()) ? current_penality : 1;
				Event::draw_card event;
				event.player = current_player;
				event.card_count = card_count;
				players.notifyOthers(
					Event::EVENT_DRAW_CARD,
					reinterpret_cast<void*>(&event),
					current_player
				);
			}

			// call actions action
			pickedAction->takeAction(this);

			// check for forgotten/bad uno, register this move
			checkUno();
			registerNonblockedPlayer(current_player);
		}

		// lets play the next player
		current_player = players.next();
	}

	{ // notify about win/game end
		Event::game_end event;
		event.winner = current_player;
		players.notifyAll(
			Event::EVENT_GAME_END,
			reinterpret_cast<void*>(&event)
		);
	}
}

SimpleCard UnoGame::lastPlayedCard() {
	SimpleCard card(deck.last_played_color, deck.last_played_value);
	return card;
}

bool UnoGame::isValidMove(UnoAction* action, std::string &message) {
	if (action == getDrawAction()) {
		return true;
	}

	UnoCard *current = static_cast<UnoCard*>(action);

	if (isPenality()) {
		if (deck.last_played_value == CARD_VALUE_PLUSFOUR) {
			if (current->getValue() == CARD_VALUE_PLUSFOUR) {
				return true;
			} else {
				message = "Must play +4 or draw";
				return false;
			}
		} else {
			if (
				current->getValue() == CARD_VALUE_PLUSFOUR ||
				current->getValue() == CARD_VALUE_PLUSTWO
			) {
				return true;
			} else {
				message = "Must play +4 or +2 or draw";
				return false;
			}
		}
	} else {
		if (current->getColor() == CARD_COLOR_BLACK) {
			return true;
		}

		if (deck.last_played_color == current->getColor()) {
			return true;
		}

		if (deck.last_played_value == current->getValue()) {
			return true;
		}

		message = "The color or the figure must match";
		return false;
	}
}

void UnoGame::blockNextPlayer() {
	players.getNextPlayer()->block();

	{
		Event::gets_blocked event;
		event.gets_blocked = players.getNextPlayer();
		event.blocked_by = players.getCurrentPlayer();

		players.notifyAll(
			Event::EVENT_GETS_BLOCKED,
			reinterpret_cast<void*>(&event)
		);
	}
}

void UnoGame::reverseTurn() {
	players.reverseTurn();
}

void UnoGame::drawCards() {
	UnoPlayer *player = players.getCurrentPlayer();

	if (isPenality()) {
		dealPenality(player);
	} else {
		dealCard(player);
	}
}

Draw *UnoGame::getDrawAction() {
	return &draw_action;
}

void UnoGame::setLastColor(CARD_COLOR color) {
	deck.last_played_color = color;

	Event::colorpick event;
	event.picked_by = players.getCurrentPlayer();
	event.color = color;
	players.notifyOthers(
		Event::EVENT_COLORPICK,
		reinterpret_cast<void*>(&event),
		players.getCurrentPlayer()
	);
}

}}} //namespace
