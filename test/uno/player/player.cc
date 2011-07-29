#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "player_concrete.h"
#include "../action/disposeable_mock.h"
#include "../action/undisposeable_mock.h"

using ::Casino::Test::Uno::Player::PlayerConcrete;
using ::Casino::Test::Uno::Action::DisposableMock;
using ::Casino::Test::Uno::Action::UndisposableMock;

TEST(UnoPlayer, getCardCount) {
	PlayerConcrete player;
	DisposableMock dis_a, dis_b, dis_c;
	UndisposableMock undis_a, undis_b, undis_c;

	ASSERT_EQ(0, player.getCardCount());

	player.addAction(&dis_a);
	player.addAction(&dis_b);
	player.addAction(&dis_c);

	ASSERT_EQ(3, player.getCardCount());

	player.addAction(&undis_a);
	player.addAction(&undis_b);
	player.addAction(&undis_c);

	ASSERT_EQ(3, player.getCardCount());

	player.removeAction(&undis_b);

	ASSERT_EQ(3, player.getCardCount());

	player.removeAction(&dis_c);

	ASSERT_EQ(2, player.getCardCount());
}
