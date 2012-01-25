#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "console_player_mock.h"
#include "../../../src/uno/action/card.h"
#include "../../../src/uno/action/simple_card.h"
#include "../../ostream_mock.h"
#include "../../istream_mock.h"

#include <iostream>

using ::Casino::Test::Uno::Player::ConsolePlayerMock;
using ::Casino::Uno::Action::SimpleCard;
using ::Casino::Test::Common::OstreamMock;
using ::Casino::Test::Common::IstreamMock;

TEST(UnoConsolePlayer, PrintCards) {
	OstreamMock output("Test/print_card_output");

	ConsolePlayerMock player(std::cin, output);
	SimpleCard
		a(::Casino::Uno::Action::CARD_COLOR_RED,
		  ::Casino::Uno::Action::CARD_VALUE_8),
		b(::Casino::Uno::Action::CARD_COLOR_BLUE,
		  ::Casino::Uno::Action::CARD_VALUE_4);



	player.addAction(&a);
	player.addAction(&b);

	player.listCards();

	output.assert_eq(
		"1. \E[37;41m\033[1m8\033[0m\E[0m\n"\
		"2. \E[37;44m\033[1m4\033[0m\E[0m\n"\
		"3. draw\n"
	);
}

TEST(UnoConsolePlayer, ChooseCard) {
	OstreamMock output("Test/choose_card_output");
	IstreamMock input("test/uno/player/choose_card_input");

	SimpleCard
		a(::Casino::Uno::Action::CARD_COLOR_RED,
		  ::Casino::Uno::Action::CARD_VALUE_8),
		b(::Casino::Uno::Action::CARD_COLOR_BLUE,
		  ::Casino::Uno::Action::CARD_VALUE_4);

	ConsolePlayerMock player(input, output);

	player.addAction(&a);
	player.addAction(&b);

	ASSERT_EQ(1, player.chooseCard());
}
