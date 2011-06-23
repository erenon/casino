#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../../../src/common/player/player.h"
#include "player_concrete.h"
#include "../action/action.h"

#include <stdexcept>

using ::Casino::Test::Common::Player::PlayerConcrete;
using ::Casino::Test::Common::Action::ActionMock;

TEST(Player, AddRemoveAction) {
	PlayerConcrete player;
	ActionMock action;

	ASSERT_EQ(0, player.getActionCount());

	player.addAction(&action);

	ASSERT_EQ(1, player.getActionCount());

	player.removeAction(&action);

	ASSERT_EQ(0, player.getActionCount());

	/*
	ASSERT_THROW(player.removeAction(&action), std::out_of_range);
	*/
}
