#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../../../src/uno/game/game.h"
#include "../player/player_mock.h"

using ::Uno::Game::Game;
using ::Test::Uno::Player::PlayerMock;

using ::testing::_;

// calling addCard on player takes a card pointer
// from the deck and passes it to the player.
// The given card must be deleted or passed back
// to avoid memory leak.
ACTION(removeCard) {
	delete arg0;
}

TEST(UnoGameGame, joinPlayer) {
	Game game(4);
	PlayerMock player;

	// initially game is empty
	ASSERT_EQ(0, game.getPlayerCount());

	game.joinPlayer(&player);
	ASSERT_EQ(1, game.getPlayerCount());
}

TEST(UnoGameGame, penalty) {
	Game game(4);

	// initially no penalty
	ASSERT_FALSE(game.isPenalty());

	game.increasePenality(4);
	ASSERT_TRUE(game.isPenalty());
}

TEST(UnoGameGame, dealPenalty) {
	Game game(4);
	PlayerMock player;

	game.joinPlayer(&player);
	game.increasePenality(4);

	EXPECT_CALL(player, addCard(_)).Times(4).WillRepeatedly(removeCard());

	game.dealPenality(&player);
}

TEST(UnoGameGame, dealCard) {
	Game game(4);
	PlayerMock player;

	game.joinPlayer(&player);
	EXPECT_CALL(player, addCard(_)).WillRepeatedly(removeCard());

	game.dealCard(&player);
}

TEST(UnoGameGame, lastPlayer) {
	Game game(4);
	PlayerMock player;

	game.registerLastPlayedPlayer(&player);
	ASSERT_EQ(&player, game.getLastPlayedPlayer());
}

TEST(UnoGameGame, block) {
	Game game(4);
	PlayerMock player;

	game.joinPlayer(&player);
	EXPECT_CALL(player, block());

	game.blockNextPlayer();
}

TEST(UnoGameGame, drawNoPenalty) {
	Game game(4);
	PlayerMock player;

	game.joinPlayer(&player);
	EXPECT_CALL(player, addCard(_)).WillRepeatedly(removeCard());

	game.drawCards();
}

TEST(UnoGameGame, drawWithPenalty) {
	Game game(4);
	PlayerMock player;

	game.joinPlayer(&player);
	game.increasePenality(6);
	EXPECT_CALL(player, addCard(_)).Times(6).WillRepeatedly(removeCard());

	game.drawCards();
}
