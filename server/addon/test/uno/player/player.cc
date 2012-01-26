#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "player_nopurevirtual.h"
#include "../action/card_mock.h"

using ::Test::Uno::Player::PlayerNopurevirtual;
using ::Test::Uno::Action::CardMock;

TEST(UnoPlayerPlayer, setGetName) {
	PlayerNopurevirtual player;
	const char* name = "Random Player";

	player.setName(name);
	ASSERT_EQ(name, player.getName());
}

TEST(UnoPlayerPlayer, addRemoveCard) {
	PlayerNopurevirtual player;
	CardMock card;

	// empty hand initially
	ASSERT_EQ(0, player.getCardCount());

	player.addCard(&card);
	ASSERT_EQ(1, player.getCardCount());

	player.removeCard(&card);
	ASSERT_EQ(0, player.getCardCount());
}

TEST(UnoPlayerPlayer, setGetUnoFlag) {
	PlayerNopurevirtual player;

	// no uno initially
	ASSERT_FALSE(player.getUnoFlag());

	player.setUnoFlag(true);
	ASSERT_TRUE(player.getUnoFlag());

	player.setUnoFlag(false);
	ASSERT_FALSE(player.getUnoFlag());
}

TEST(UnoPlayerPlayer, blockUnblock) {
	PlayerNopurevirtual player;

	// no block initially
	ASSERT_FALSE(player.isBlocked());

	player.block();
	ASSERT_TRUE(player.isBlocked());

	player.unblock();
	ASSERT_FALSE(player.isBlocked());
}
