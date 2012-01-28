#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../../../src/uno/game/player_list.h"
#include "../../../src/uno/event/event.h"
#include "../player/player_mock.h"

using ::Uno::Game::PlayerList;
using ::Test::Uno::Player::PlayerMock;

TEST(UnoGamePlayerList, joinPlayer) {
	PlayerList list;
	PlayerMock player;

	ASSERT_EQ(0, list.size());

	list.joinPlayer(&player);
	ASSERT_EQ(1, list.size());
}

TEST(UnoGamePlayerList, prevCurNextPlayer) {
	PlayerList list;
	PlayerMock alice, bob, charlie;

	list.joinPlayer(&alice);
	list.joinPlayer(&bob);
	list.joinPlayer(&charlie);

	ASSERT_EQ(&alice, list.getCurrentPlayer());
	ASSERT_EQ(&bob, list.getNextPlayer());
	// prev player is null

	list.next();

	ASSERT_EQ(&alice, list.getPreviousPlayer());
	ASSERT_EQ(&bob, list.getCurrentPlayer());
	ASSERT_EQ(&charlie, list.getNextPlayer());
}

TEST(UnoGamePlayerList, reverseTurn) {
	PlayerList list;
	PlayerMock alice, bob, charlie;

	list.joinPlayer(&alice);
	list.joinPlayer(&bob);
	list.joinPlayer(&charlie);

	list.next();
	list.reverseTurn();

	// Prev player is alice,
	// becouse it points to the previously played player.
	ASSERT_EQ(&alice, list.getPreviousPlayer());
	ASSERT_EQ(&bob, list.getCurrentPlayer());
	ASSERT_EQ(&alice, list.getNextPlayer());
}

TEST(UnoGamePlayerList, reverseTurnB) {
	PlayerList list;
	PlayerMock alice, bob, charlie;

	list.joinPlayer(&alice);
	list.joinPlayer(&bob);
	list.joinPlayer(&charlie);

	list.next(); // bob
	list.next(); // charlie
	list.reverseTurn();
	list.next(); // bob

	// Prev player is alice,
	// becouse it points to the previously played player.
	ASSERT_EQ(&charlie, list.getPreviousPlayer());
	ASSERT_EQ(&bob, list.getCurrentPlayer());
	ASSERT_EQ(&alice, list.getNextPlayer());
}

TEST(UnoGamePlayerList, reset) {
	PlayerList list;
	PlayerMock alice, bob;

	list.joinPlayer(&alice);
	list.joinPlayer(&bob);

	list.next();
	list.reset();

	ASSERT_EQ(&alice, list.getCurrentPlayer());
	ASSERT_EQ(&bob, list.getNextPlayer());
}

TEST(UnoGamePlayerList, notifyAll) {
	PlayerList list;
	PlayerMock alice, bob;
	::Uno::Event::EVENT event_type = ::Uno::Event::EVENT_CARD_PLAYED;
	void* event = static_cast<void*>(&alice);

	list.joinPlayer(&alice);
	list.joinPlayer(&bob);

	EXPECT_CALL(alice, notify(event_type, event));
	EXPECT_CALL(bob, notify(event_type, event));

	list.notifyAll(event_type, event);
}

TEST(UnoGamePlayerList, notifyOthers) {
	PlayerList list;
	PlayerMock alice, bob, charlie;
	::Uno::Event::EVENT event_type = ::Uno::Event::EVENT_CARD_PLAYED;
	void* event = static_cast<void*>(&alice);

	list.joinPlayer(&alice);
	list.joinPlayer(&bob);
	list.joinPlayer(&charlie);

	EXPECT_CALL(alice, notify(event_type, event));
	EXPECT_CALL(charlie, notify(event_type, event));

	list.notifyOthers(event_type, event, &bob);
}
