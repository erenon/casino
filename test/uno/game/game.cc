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
using ::testing::InSequence;
using ::testing::Return;
//using ::testing::Invoke;
using ::testing::DoAll;

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

//TEST(UnoGame, LastPlayedCard) {

ACTION_P2(isLastPlayedCardValid, begin, end) {
	ASSERT_TRUE(
		begin <= arg0->lastPlayedCard()
	&&  end >= arg0->lastPlayedCard()
	);
}

ACTION(BlockNextPlayer) {
	arg0->blockNextPlayer();
}

ACTION_P(isLastPlayedCardExactly, card) {
	ASSERT_TRUE(card == arg0->lastPlayedCard());
}

ACTION(ReverseTurn) {
	arg0->reverseTurn();
}

ACTION(plusTwoCardAction) {
	arg0->increasePenality(2);
}

ACTION_P(drawTwoCards, player) {
	arg0->dealPenality(player);
}

#define CARD_COUNT 30

#define START_TURN(PLY)						\
		EXPECT_CALL(PLY, isBlocked())		\
			.WillOnce(Return(false))		\
			.RetiresOnSaturation();			\
											\
		EXPECT_CALL(PLY, getCardCount())	\
			.WillOnce(Return(7))			\
			.RetiresOnSaturation();			\
											\
		EXPECT_CALL(PLY, isBlocked())		\
			.WillOnce(Return(false))		\
			.RetiresOnSaturation();			\

#define PLAY_OUT_CARD(CARD, PLY)			\
		EXPECT_CALL(CARD, isDisposeable())	\
			.WillOnce(Return(true))			\
			.RetiresOnSaturation();			\
											\
		EXPECT_CALL(PLY, removeAction(&(CARD)))	\
			.RetiresOnSaturation();			\

#define UNO_CHECK(PLY)						\
		EXPECT_CALL(PLY, wrongUno())		\
			.WillOnce(Return(false))		\
			.RetiresOnSaturation();			\
											\
		EXPECT_CALL(PLY, setUnoFlag(false))	\
			.RetiresOnSaturation();			\

TEST(UnoGame, Gameplay) {
	UnoGame game(3);
	UnoPlayerMock alice, bob, charlie;
	CardMock cards[CARD_COUNT];
	CardMock draw;

	game.joinPlayer(&alice);
	game.joinPlayer(&bob);
	game.joinPlayer(&charlie);


	{	// deal initial hands
		InSequence s;

		const int initial_hand_size = 7;
		for (int i = 0; i < initial_hand_size; i++) {
			EXPECT_CALL(alice, addAction(_))
				.RetiresOnSaturation();
			EXPECT_CALL(bob, addAction(_))
				.RetiresOnSaturation();
			EXPECT_CALL(charlie, addAction(_))
				.RetiresOnSaturation();
		}

	}

	{	// check win if not blocked, check block,
		// then ask for action
		InSequence s;

		// alice - blocks bob
		START_TURN(alice);

		EXPECT_CALL(alice, pickAction(&game))
			.WillOnce(DoAll(
				// check whether the first autoplayed card was in the deck
				isLastPlayedCardValid(&(cards[0]), &(cards[CARD_COUNT - 1])),
				Return(&(cards[0]))
			))
			.RetiresOnSaturation();

		EXPECT_CALL(cards[0], takeAction(&game))
			.WillOnce(BlockNextPlayer())
			.RetiresOnSaturation();

		EXPECT_CALL(bob, block())
			.RetiresOnSaturation();

		PLAY_OUT_CARD(cards[0], alice);

		// bob - gets blocked
		EXPECT_CALL(bob, isBlocked())
			.Times(2)
			.WillOnce(Return(true))
			.WillOnce(Return(true))
			.RetiresOnSaturation();

		EXPECT_CALL(bob, unblock())
			.RetiresOnSaturation();

		UNO_CHECK(alice);

		// charlie - reverses turn
		START_TURN(charlie);

		EXPECT_CALL(charlie, pickAction(&game))
			.WillOnce(DoAll(
				// check whether the prev played card is the last
				isLastPlayedCardExactly(&(cards[0])),
				Return(&(cards[1]))
			))
			.RetiresOnSaturation();

		EXPECT_CALL(cards[1], takeAction(&game))
			.WillOnce(ReverseTurn())
			.RetiresOnSaturation();

		PLAY_OUT_CARD(cards[1], charlie);
		UNO_CHECK(bob);

		// bob - revenge, +2 to alice
		START_TURN(bob);

		EXPECT_CALL(bob, pickAction(&game))
			.WillOnce(Return(&(cards[2])))
			.RetiresOnSaturation();

		EXPECT_CALL(cards[2], takeAction(&game))
			.WillOnce(plusTwoCardAction())
			.RetiresOnSaturation();

		PLAY_OUT_CARD(cards[2], bob);
		UNO_CHECK(charlie);

		// alice - draw two cards
		START_TURN(alice);

		EXPECT_CALL(alice, pickAction(&game))
			.WillOnce(Return(&draw))
			.RetiresOnSaturation();

		EXPECT_CALL(draw, takeAction(&game))
			.WillOnce(drawTwoCards(&alice))
			.RetiresOnSaturation();

		EXPECT_CALL(alice, addAction(_))
			.RetiresOnSaturation();
		EXPECT_CALL(alice, addAction(_))
			.RetiresOnSaturation();

		EXPECT_CALL(draw, isDisposeable())
			.WillOnce(Return(false))
			.RetiresOnSaturation();

		UNO_CHECK(bob);

		// charlie wins
		EXPECT_CALL(charlie, isBlocked())
			.WillOnce(Return(false))
			.RetiresOnSaturation();

		EXPECT_CALL(charlie, getCardCount())
			.WillOnce(Return(0))
			.RetiresOnSaturation();
	}

	for (int i = 0; i < CARD_COUNT; i++) {
		game.addCardToDeck(&(cards[i]));
	}
	game.start();
}

#undef CARD_COUNT
#undef START_TURN
#undef PLAY_OUT_CARD
#undef UNO_CHECK
