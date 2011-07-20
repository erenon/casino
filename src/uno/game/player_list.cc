#include "game.h"

#include "../player/player.h"

#include <list>

namespace Casino { namespace Uno { namespace Game {

using ::Casino::Uno::Player::UnoPlayer;

UnoGame::PlayerList::PlayerList()
	:turn_direction_normal(true),
	 prev_player(NULL)
{
	current_player = players.begin();
}

void UnoGame::PlayerList::joinPlayer(UnoPlayer* player) {
	players.push_back(player);
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

void UnoGame::PlayerList::notifyAll(Event::EVENT event_type, void* event) {
	player_iterator it;

	for (it = players.begin(); it != players.end(); it++) {
		(*it)->notify(event_type, event);
	}
}

void UnoGame::PlayerList::notifyOthers(Event::EVENT event_type, void* event, UnoPlayer* player) {
	player_iterator it;

	for (it = players.begin(); it != players.end(); it++) {
		if (*it != player) {
			(*it)->notify(event_type, event);
		}
	}
}

void UnoGame::PlayerList::reset() {
	prev_player = NULL;
	current_player = players.begin();
}

void UnoGame::PlayerList::reverseTurn() {
	turn_direction_normal = !turn_direction_normal;
}

}}} //namespace
