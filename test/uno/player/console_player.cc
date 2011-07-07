#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "console_player_mock.h"
#include "../../../src/uno/action/card.h"
#include "../../../src/uno/action/simple_card.h"
#include "../../ostream_mock.h"
#include "../../istream_mock.h"

#include <iostream>

using ::Casino::Test::Uno::Player::ConsoleUnoPlayerMock;
using ::Casino::Uno::Action::SimpleCard;
using ::Casino::Test::Common::OstreamMock;
using ::Casino::Test::Common::IstreamMock;

TEST(ConsoleUnoPlayer, PrintCards) {
	OstreamMock output("Test/print_card_output");

	ConsoleUnoPlayerMock player(std::cin, output);
	SimpleCard
		a(::Casino::Uno::Action::CARD_COLOR_RED,
		  ::Casino::Uno::Action::CARD_VALUE_8),
		b(::Casino::Uno::Action::CARD_COLOR_BLUE,
		  ::Casino::Uno::Action::CARD_VALUE_4);



	player.addAction(&a);
	player.addAction(&b);

	player.listCards();

	output.assert_eq("1. R8\n2. B4\n3. draw\n");
}

TEST(ConsoleUnoPlayer, ChooseCard) {
	OstreamMock output("Test/choose_card_output");
	IstreamMock input("test/uno/player/choose_card_input");

	SimpleCard
		a(::Casino::Uno::Action::CARD_COLOR_RED,
		  ::Casino::Uno::Action::CARD_VALUE_8),
		b(::Casino::Uno::Action::CARD_COLOR_BLUE,
		  ::Casino::Uno::Action::CARD_VALUE_4);

	ConsoleUnoPlayerMock player(input, output);

	player.addAction(&a);
	player.addAction(&b);

	ASSERT_EQ(1, player.chooseCard());
}
