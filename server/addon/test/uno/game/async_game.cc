#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../../../src/uno/game/async_game.h"
#include "../../../src/uno/event/event.h"
#include "../player/player_mock.h"

using ::Uno::Game::AsyncGame;
using ::Uno::Event::EVENT;
using ::Test::Uno::Player::PlayerMock;

using ::testing::_;
using ::testing::Return;

// calling addCard on player takes a card pointer
// from the deck and passes it to the player.
// The given card must be deleted or passed back
// to avoid memory leak.
ACTION(removeCard) {
	delete arg0;
}

TEST(UnoGameAsyncGame, start) {
	AsyncGame game(4);
	PlayerMock player;

	game.joinPlayer(&player);

	EXPECT_CALL(player, addCard(_)).Times(7).WillRepeatedly(removeCard());

	EXPECT_CALL(player, notify(::Uno::Event::EVENT_GAME_START, _));
	EXPECT_CALL(player, notify(::Uno::Event::EVENT_PLAYERS_TURN, _));

	game.start();
}

TEST(UnoGameAsyncGame, checkUnoNoUnoGood) {
	AsyncGame game(4);
	PlayerMock player;

	game.joinPlayer(&player);
	game.registerLastPlayedPlayer(&player);

	EXPECT_CALL(player, getCardCount()).WillRepeatedly(Return(5));
	EXPECT_CALL(player, getUnoFlag()).WillRepeatedly(Return(false));

	// no uno, more than one card, -> no addCard
	EXPECT_CALL(player, addCard(_)).Times(0);

	game.checkUno();
}

TEST(UnoGameAsyncGame, checkUnoUnoGood) {
	AsyncGame game(4);
	PlayerMock player;

	game.joinPlayer(&player);
	game.registerLastPlayedPlayer(&player);

	EXPECT_CALL(player, getCardCount()).WillRepeatedly(Return(1));
	EXPECT_CALL(player, getUnoFlag()).WillRepeatedly(Return(true));

	// uno, one card, -> no addCard
	EXPECT_CALL(player, addCard(_)).Times(0);

	game.checkUno();
}

TEST(UnoGameAsyncGame, checkUnoUnoNoGood) {
	AsyncGame game(4);
	PlayerMock player;

	game.joinPlayer(&player);
	game.registerLastPlayedPlayer(&player);

	EXPECT_CALL(player, getCardCount()).WillRepeatedly(Return(3));
	EXPECT_CALL(player, getUnoFlag()).WillRepeatedly(Return(true));

	// uno, more than one card, -> some addCard
	EXPECT_CALL(player, addCard(_)).Times(2).WillRepeatedly(removeCard());

	game.checkUno();
}

TEST(UnoGameAsyncGame, checkUnoNoUnoNoGood) {
	AsyncGame game(4);
	PlayerMock player;

	game.joinPlayer(&player);
	game.registerLastPlayedPlayer(&player);

	EXPECT_CALL(player, getCardCount()).WillRepeatedly(Return(1));
	EXPECT_CALL(player, getUnoFlag()).WillRepeatedly(Return(false));

	// no uno, one card, -> some addCard
	EXPECT_CALL(player, addCard(_)).Times(2).WillRepeatedly(removeCard());

	game.checkUno();
}

// TODO test takeAction
