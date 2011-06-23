#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../../../src/common/game/game.h"
#include "../player/player_mock.h"

#include <stdexcept>

using ::Casino::Common::Game::Game;
using ::Casino::Test::Common::Player::PlayerMock;

TEST(Game, MaxPlayerInvalid) {
	ASSERT_THROW(Game game(-1), std::underflow_error);
	ASSERT_THROW(Game game(0), std::underflow_error);
}

TEST(Game, GetPlayerCount) {
	Game game(5);

	PlayerMock alice;

	ASSERT_EQ(0, game.getPlayerCount());

	game.joinPlayer(&alice);

	ASSERT_EQ(1, game.getPlayerCount());
}

TEST(Game, PlayerLimit) {
	Game game(2);

	PlayerMock alice, bob, charlie;

	ASSERT_NO_THROW(game.joinPlayer(&alice));
	ASSERT_NO_THROW(game.joinPlayer(&bob));
	ASSERT_THROW(game.joinPlayer(&charlie), std::overflow_error);
}
