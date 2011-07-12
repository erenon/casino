#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <stdexcept>

#include "../../../src/uno/game/game.h"
#include "../../../src/uno/action/card.h"
#include "../../../src/uno/action/simple_card.h"
#include "../../../src/uno/event/event.h"
#include "../player/player_mock.h"
#include "../action/card_mock.h"

using ::Casino::Uno::Game::UnoGame;
using ::Casino::Test::Uno::Player::UnoPlayerMock;
using ::Casino::Test::Uno::Action::CardMock;
using namespace ::Casino::Uno::Action;	//SimpleCard, CARD_COLOR/VALUE
namespace Event = ::Casino::Uno::Event;
using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;
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

ACTION(isFirstCardValid) {
	SimpleCard c = arg0->lastPlayedCard();
	ASSERT_NE(c.getColor(), CARD_COLOR_BLACK);
	ASSERT_NE(c.getValue(), CARD_VALUE_BLOCK);
	ASSERT_NE(c.getValue(), CARD_VALUE_REVERSE);
	ASSERT_NE(c.getValue(), CARD_VALUE_PLUSTWO);
}

ACTION(BlockNextPlayer) {
	arg0->blockNextPlayer();
}

ACTION_P(isLastPlayedCardExactly, card) {
	ASSERT_EQ(card->getColor(), arg0->lastPlayedCard().getColor());
	ASSERT_EQ(card->getValue(), arg0->lastPlayedCard().getValue());
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

#define PLAY_OUT_CARD(CARD, PLY, OTHER1, OTHER2)\
		EXPECT_CALL(CARD, isDisposeable())	\
			.WillOnce(Return(true))			\
			.RetiresOnSaturation();			\
											\
		EXPECT_CALL(PLY, removeAction(&(CARD)))	\
			.RetiresOnSaturation();			\
											\
		EXPECT_CALL(OTHER1, notify(Event::EVENT_CARD_PLAYED, _)) \
			.RetiresOnSaturation();			\
											\
		EXPECT_CALL(OTHER2, notify(Event::EVENT_CARD_PLAYED, _)) \
			.RetiresOnSaturation();			\

#define UNO_CHECK(PLY)						\
		EXPECT_CALL(PLY, getCardCount())	\
			.WillOnce(Return(5))			\
			.RetiresOnSaturation();			\
											\
		EXPECT_CALL(PLY, getUnoFlag())		\
			.WillOnce(Return(false))		\
			.RetiresOnSaturation();			\

ACTION_P2(checkBlockNotify, blocker, blocked) {
	Event::gets_blocked* e = reinterpret_cast<Event::gets_blocked*>(arg1);
	ASSERT_EQ(blocker, e->blocked_by);
	ASSERT_EQ(blocked, e->gets_blocked);
}

#define EXPECT_NOTIFY_BLOCK(BLOCKER, BLOCKED, NOT1, NOT2, NOT3) \
		EXPECT_CALL(NOT1, notify(Event::EVENT_GETS_BLOCKED, _)) \
			.WillOnce(checkBlockNotify(&BLOCKER, &BLOCKED))		\
			.RetiresOnSaturation();								\
		EXPECT_CALL(NOT2, notify(Event::EVENT_GETS_BLOCKED, _)) \
			.WillOnce(checkBlockNotify(&BLOCKER, &BLOCKED))		\
			.RetiresOnSaturation();								\
		EXPECT_CALL(NOT3, notify(Event::EVENT_GETS_BLOCKED, _)) \
			.WillOnce(checkBlockNotify(&BLOCKER, &BLOCKED))		\
			.RetiresOnSaturation();								\

ACTION_P2(checkDrawNotify, draws, count) {
	Event::draw_card* e = reinterpret_cast<Event::draw_card*>(arg1);
	ASSERT_EQ(draws, e->player);
	ASSERT_EQ(count, e->card_count);
}

#define EXPECT_NOTIFY_DRAW(DRAWS, COUNT, NOT1, NOT2)			\
		EXPECT_CALL(NOT1, notify(Event::EVENT_DRAW_CARD, _))	\
			.WillOnce(checkDrawNotify(&DRAWS, COUNT))			\
			.RetiresOnSaturation();								\
		EXPECT_CALL(NOT2, notify(Event::EVENT_DRAW_CARD, _))	\
			.WillOnce(checkDrawNotify(&DRAWS, COUNT))			\
			.RetiresOnSaturation();								\

ACTION_P(checkGameEndNotify, winner) {
	Event::game_end* e = reinterpret_cast<Event::game_end*>(arg1);
	ASSERT_EQ(winner, e->winner);
}

#define EXPECT_NOTIFY_END(WINNER, NOT1, NOT2, NOT3)				\
		EXPECT_CALL(NOT1, notify(Event::EVENT_GAME_END, _))		\
			.WillOnce(checkGameEndNotify(&WINNER))				\
			.RetiresOnSaturation();								\
		EXPECT_CALL(NOT2, notify(Event::EVENT_GAME_END, _))		\
			.WillOnce(checkGameEndNotify(&WINNER))				\
			.RetiresOnSaturation();								\
		EXPECT_CALL(NOT3, notify(Event::EVENT_GAME_END, _))		\
			.WillOnce(checkGameEndNotify(&WINNER))				\
			.RetiresOnSaturation();								\

TEST(UnoGame, Gameplay) {
	UnoGame game(3);
	UnoPlayerMock alice, bob, charlie;
	CardMock cards[CARD_COUNT];
	SimpleCard first_card(CARD_COLOR_RED, CARD_VALUE_6);
	CardMock draw;

	game.joinPlayer(&alice);
	game.joinPlayer(&bob);
	game.joinPlayer(&charlie);

	{	//game start
		Event::EVENT start = Event::EVENT_GAME_START;
		EXPECT_CALL(alice, notify(start, _))
			.RetiresOnSaturation();
		EXPECT_CALL(bob, notify(start, _))
			.RetiresOnSaturation();
		EXPECT_CALL(charlie, notify(start, _))
			.RetiresOnSaturation();
	}

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
				// check whether the first autoplayed card is simple
				isFirstCardValid(),
				Return(&(cards[0]))
			))
			.RetiresOnSaturation();

		PLAY_OUT_CARD(cards[0], alice, bob, charlie);

		EXPECT_CALL(cards[0], takeAction(&game))
			.WillOnce(BlockNextPlayer())
			.RetiresOnSaturation();

		EXPECT_CALL(bob, block())
			.RetiresOnSaturation();

		EXPECT_NOTIFY_BLOCK(alice, bob, alice, bob, charlie);

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

		PLAY_OUT_CARD(cards[1], charlie, alice, bob);

		EXPECT_CALL(cards[1], takeAction(&game))
			.WillOnce(ReverseTurn())
			.RetiresOnSaturation();

		UNO_CHECK(bob);

		// bob - revenge, +2 to alice
		START_TURN(bob);

		EXPECT_CALL(bob, pickAction(&game))
			.WillOnce(Return(&(cards[2])))
			.RetiresOnSaturation();

		PLAY_OUT_CARD(cards[2], bob, alice, charlie);

		EXPECT_CALL(cards[2], takeAction(&game))
			.WillOnce(plusTwoCardAction())
			.RetiresOnSaturation();

		UNO_CHECK(charlie);

		// alice - draw two cards
		START_TURN(alice);

		EXPECT_CALL(alice, pickAction(&game))
			.WillOnce(Return(&draw))
			.RetiresOnSaturation();

		EXPECT_CALL(draw, isDisposeable())
			.WillOnce(Return(false))
			.RetiresOnSaturation();

		EXPECT_NOTIFY_DRAW(alice, 2, bob, charlie);

		EXPECT_CALL(draw, takeAction(&game))
			.WillOnce(drawTwoCards(&alice))
			.RetiresOnSaturation();

		EXPECT_CALL(alice, addAction(_))
			.RetiresOnSaturation();
		EXPECT_CALL(alice, addAction(_))
			.RetiresOnSaturation();

		UNO_CHECK(bob);

		// charlie wins
		EXPECT_CALL(charlie, isBlocked())
			.WillOnce(Return(false))
			.RetiresOnSaturation();

		EXPECT_CALL(charlie, getCardCount())
			.WillOnce(Return(0))
			.RetiresOnSaturation();

		EXPECT_NOTIFY_END(charlie, alice, bob, charlie);
	}

	for (int i = 0; i < CARD_COUNT; i++) {
		game.addCardToDeck(&(cards[i]));
	}
	game.addCardToDeck(&first_card);
	game.start();
}

#undef CARD_COUNT
#undef START_TURN
#undef PLAY_OUT_CARD
#undef UNO_CHECK
#undef EXPECT_NOTIFY_BLOCK
#undef EXPECT_NOTIFY_DRAW
#undef EXPECT_NOTIFY_END
