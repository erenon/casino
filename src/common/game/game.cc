#include "game.h"
#include "../player/player.h"

#include <stdexcept>

namespace Casino { namespace Common { namespace Game {

using ::Casino::Common::Player::Player;

Game::Game(int max_player_count) :max_player_count(max_player_count) {
	if (max_player_count < 1) {
		throw std::underflow_error(
			"Maximum player count must be equal or greater than 1"
		);
	}

	player_count = 0;
	players = new Player*[max_player_count];
}

void Game::joinPlayer(Player *player) {
	if (player_count >= max_player_count) {
		throw std::overflow_error("Game is full");
	}

	players[player_count] = player;
	player_count++;
}

int Game::getPlayerCount() {
	return player_count;
}

Game::~Game() {
	delete[] players;
}


}}} //namespace
