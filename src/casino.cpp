#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "uno/game/game.h"
#include "uno/player/console_player.h"
#include "uno/action/full_card_deck.h"

using ::Casino::Uno::Game::UnoGame;
using ::Casino::Uno::Player::ConsoleUnoPlayer;
using ::Casino::Uno::Action::UnoFullCardDeck;

int main(void) {
	printf("casino main hello");

	UnoGame game(2);
	ConsoleUnoPlayer
		alice(std::cin, std::cout),
		bob(std::cin, std::cout);
	UnoFullCardDeck deck;

	deck.fillGameWithCards(&game);

	game.joinPlayer(&alice);
	game.joinPlayer(&bob);

	game.start();

	return EXIT_SUCCESS;
}
