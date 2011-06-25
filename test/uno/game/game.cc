#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <stdexcept>

#include "../../../src/uno/game/game.h"
#include "../player/player_mock.h"
#include "../action/card_mock.h"

using ::Casino::Uno::Game::UnoGame;
using ::Casino::Test::Uno::Player::UnoPlayerMock;
using ::Casino::Test::Uno::Action::CardMock;
using ::testing::_;

TEST(UnoGame, Penality) {
	UnoGame game(1);
	UnoPlayerMock player;
	CardMock card_a, card_b;

	// add cards to deck (game)
	game.addCardToDeck(&card_a);
	game.addCardToDeck(&card_b);

	// no penality as the game starts
	ASSERT_FALSE(game.isPenality());

	// add some penality
	game.increasePenality(2);

	// penality increased
	ASSERT_TRUE(game.isPenality());

	// player gets cards
	EXPECT_CALL(player, addAction(&card_a));
	EXPECT_CALL(player, addAction(&card_b));

	game.dealPenality(&player);

	// after deal, no penality is present
	ASSERT_FALSE(game.isPenality());
}

TEST(UnoGame, DealCard) {
	UnoGame game(1);
	UnoPlayerMock player;
	CardMock card_a;

	game.addCardToDeck(&card_a);

	EXPECT_CALL(player, addAction(&card_a));
	game.dealCard(&player);

	// deck is empty
	ASSERT_THROW(game.dealCard(&player), std::length_error);
}
