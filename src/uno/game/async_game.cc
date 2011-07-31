#include "async_game.h"

#include "../event/event.h"
#include "../action/simple_card.h"

#include <string>

namespace Casino { namespace Uno { namespace Game {

namespace Event = ::Casino::Uno::Event;
using ::Casino::Uno::Action::SimpleCard;

AsyncGame::AsyncGame(int max_player_count)
	:Casino::Uno::Game::Game(max_player_count)
{

}

void AsyncGame::start() {
	// prepare deck
	deck.shuffleDeck();
	deck.playOutFirstCard();

	// deal initial hands
	std::list<Player *>::iterator player;
	for (int card_idx = 0; card_idx < config.initial_hand_size; card_idx++) {
		players.reset();
		for (int i = 0; i < players.size(); i++, players.next()) {
			players.getCurrentPlayer()->addAction(deck.drawCard());
		}
	}

	{   // send game start event
		Event::game_start event;
		SimpleCard first_card(
			deck.last_played_color,
			deck.last_played_value
		);
		event.first_card = &first_card;
		players.notifyAll(
			Event::EVENT_GAME_START,
			reinterpret_cast<void*>(&event)
		);
	}

	{   // start the first turn
		players.reset();
		Event::players_turn event;
		event.player = players.getCurrentPlayer();
		players.notifyAll(
			Event::EVENT_PLAYERS_TURN,
			reinterpret_cast<void*>(&event)
		);
	}
}

/**
 * @todo use enum status instead of string,
 * tweak takeAction to it after
 */
bool AsyncGame::isValidMove(Player* player, Action* action, std::string &message) {
	if (action == getDrawAction() && player == players.getCurrentPlayer()) {
		return true;
	}

	Card *card = static_cast<Card*>(action);

	// current player or same card
	if (
		deck.last_played_color == card->getColor()
	&&  deck.last_played_value == card->getValue()
	) {
		return true;
	} else if (player != players.getCurrentPlayer()) {
		message = "Not your turn";
		return false;
	}

	if (isPenalty()) {
		if (deck.last_played_value == CARD_VALUE_PLUSFOUR) {
			if (card->getValue() == CARD_VALUE_PLUSFOUR) {
				return true;
			} else {
				message = "Must play +4 or draw";
				return false;
			}
		} else {
			if (
				card->getValue() == CARD_VALUE_PLUSFOUR ||
				card->getValue() == CARD_VALUE_PLUSTWO
			) {
				return true;
			} else {
				message = "Must play +4 or +2 or draw";
				return false;
			}
		}
	} else {
		if (card->getColor() == CARD_COLOR_BLACK) {
			return true;
		}

		if (deck.last_played_color == card->getColor()) {
			return true;
		}

		if (deck.last_played_value == card->getValue()) {
			return true;
		}

		message = "The color or the figure must match";
		return false;
	}
}

void AsyncGame::takeAction(Player* player, Action* action) {
	std::string message;
	bool is_valid = false;
	is_valid = isValidMove(player, action, message);

	if (!is_valid) {
		throw message;
	}

	if (action->isDisposeable()) {
		player->removeAction(action);

		Card* played_card = static_cast<Card*>(action);
		deck.last_played_color = played_card->getColor();
		deck.last_played_value = played_card->getValue();
		deck.addCardToPlayed(played_card);

		{ //notify about played card
			Event::card_played event;
			SimpleCard played_card(
				deck.last_played_color,
				deck.last_played_value
			);
			event.played_card = &played_card;
			event.played_by = player;
			players.notifyOthers(
				Event::EVENT_CARD_PLAYED,
				reinterpret_cast<void*>(&event),
				player
			);
		}
	}

	// call actions action
	action->takeAction(this);

	// check for forgotten uno
	/** @todo implement this */
	//checkUno();

	// determine next player
	Player* next_player;
	do {
		players.next();
		next_player = players.getCurrentPlayer();
	} while (next_player->isBlocked() == false);

	{   // notify about the next player
		Event::players_turn event;
		event.player = players.getCurrentPlayer();
		players.notifyAll(
			Event::EVENT_PLAYERS_TURN,
			reinterpret_cast<void*>(&event)
		);
	}
}

void AsyncGame::drawCards() {
	//player draws the current penalty or a single card
	int card_count = (isPenalty()) ? current_penalty : 1;

	Game::drawCards();

	Event::draw_card event;
	event.player = players.getCurrentPlayer();
	event.card_count = card_count;
	players.notifyOthers(
		Event::EVENT_DRAW_CARD,
		reinterpret_cast<void*>(&event),
		players.getCurrentPlayer()
	);
}

}}} //namespace
