#include "game.h"

namespace Casino { namespace Uno { namespace Game {

Game::Game(int max_player_count)
	:Casino::Common::Game::Game(max_player_count),
	 current_penalty(0)
{

}

//
// PENALTY
//

bool Game::isPenalty() {
	return (current_penalty > 0);
}

void Game::increasePenality(int addition) {
	current_penalty += addition;
}

void Game::dealPenality(Player* player) {
	for (int i = 0; i < current_penalty; i++) {
		dealCard(player);
	}

	current_penalty = 0;
}

void Game::dealCard(Player* player) {
	Card* top_card = deck.drawCard();
	player->addAction(top_card);
}


/**
 * @todo don't expose addCard this way,
 * dependency inject deck instead.
 */
void Game::addCardToDeck(Card *card) {
	deck.addCard(card);
}

//
// CARD ACTIONS
//

void Game::blockNextPlayer() {
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

void Game::reverseTurn() {
	players.reverseTurn();
}

void Game::drawCards() {
	Player *player = players.getCurrentPlayer();

	if (isPenalty()) {
		dealPenality(player);
	} else {
		dealCard(player);
	}
}

Draw *Game::getDrawAction() {
	return &draw_action;
}

void Game::setLastColor(CARD_COLOR color) {
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
