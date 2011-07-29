#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "uno/game/game.h"
#include "uno/player/console_player.h"
#include "uno/player/robot_easy_player.h"
#include "uno/action/full_card_deck.h"

using ::Casino::Uno::Game::Game;
using ::Casino::Uno::Player::ConsoleUnoPlayer;
using ::Casino::Uno::Player::RobotEasyUnoPlayer;
using ::Casino::Uno::Action::FullCardDeck;

int main(void) {
	printf("===Casino Uno\n");

	Game game(4);
	ConsoleUnoPlayer alice(std::cin, std::cout);
	RobotEasyUnoPlayer robots[3];
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
