#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "uno/game/console_game.h"
#include "uno/player/console_player.h"
#include "uno/player/robot_easy_player.h"
#include "uno/action/full_card_deck.h"

using ::Casino::Uno::Game::ConsoleGame;
using ::Casino::Uno::Player::ConsolePlayer;
using ::Casino::Uno::Player::RobotEasyPlayer;
using ::Casino::Uno::Action::FullCardDeck;

int main(void) {
	printf("===Casino Uno\n");

	ConsoleGame game(4);
	ConsolePlayer alice(std::cin, std::cout);
	RobotEasyPlayer robots[3];
	FullCardDeck deck;

	alice.setName("player");
	robots[0].setName("robot 1");
	robots[1].setName("robot 2");
	robots[2].setName("robot 3");

	deck.fillGameWithCards(&game);

	game.joinPlayer(&alice);
	game.joinPlayer(&(robots[0]));
	game.joinPlayer(&(robots[1]));
	game.joinPlayer(&(robots[2]));

	game.start();

	return EXIT_SUCCESS;
}
