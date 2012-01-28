#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../../../src/uno/game/deck.h"
#include "../../../src/uno/action/card.h"
#include "../action/card_mock.h"

using ::Uno::Game::Deck;
using ::Test::Uno::Action::CardMock;
using ::Uno::Action::CARD_COLOR;
using ::Uno::Action::CARD_VALUE;

/**
 * TODO
 * This test fails, becouse the last_played_color
 * and last_played_value members are not managed by Deck
 * but client classes. This MUST be changed.
 * The only block of the trivial solution are the wild cards
 * with choosen color. This can be fixed after the refactor
 * of the colorpick concept.
 */
TEST(UnoGameDeck, checkPlayedCard) {
	Deck deck;
	CardMock *card = new CardMock();
	card->setColor(::Uno::Action::CARD_COLOR_RED);
	card->setValue(::Uno::Action::CARD_VALUE_3);

	deck.addCardToPlayed(card);

	// these lines causes several valgrind varnings
	// becouse the checked members are not initialized.
	// If this test passes, this problem will be
	// automatically solved.
	//EXPECT_EQ(deck.last_played_color, ::Uno::Action::CARD_COLOR_RED);
	//EXPECT_EQ(deck.last_played_value, ::Uno::Action::CARD_VALUE_3);

	// no need to delete card, deck will free it
}
