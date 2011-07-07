#include "console_player.h"
#include <iostream>
#include "../action/card.h"
#include <limits> //for istream ignore

namespace Casino { namespace Uno { namespace Player {

/*using ::Casino::Uno::Action::UnoCard;
using ::Casino::Uno::Action::CARD_COLOR;
using ::Casino::Uno::Action::CARD_VALUE;*/
using namespace ::Casino::Uno::Action;

ConsoleUnoPlayer::ConsoleUnoPlayer(
	std::istream& in,
	std::ostream& out
)
	:in(in),
	out(out)
{}

void ConsoleUnoPlayer::println(const char* str) {
	out << str << std::endl;
}

std::ostream& operator<<(std::ostream& out, UnoCard *card) {

	// print color
	switch (card->getColor()) {
	case CARD_COLOR_RED:
		out << 'R';
		break;
	case CARD_COLOR_GREEN:
		out << 'G';
		break;
	case CARD_COLOR_BLUE:
		out << 'B';
		break;
	case CARD_COLOR_YELLOW:
		out << 'Y';
		break;
	case CARD_COLOR_BLACK:
		break;
	default:
		out << '?';
		break;
	}

	//print value
#define CASE_CARD_VALUE(V,O) \
	case CARD_VALUE_##V: \
		out << O; \
		break;

	switch (card->getValue()) {
		CASE_CARD_VALUE(0,"0");
		CASE_CARD_VALUE(1,"1");
		CASE_CARD_VALUE(2,"2");
		CASE_CARD_VALUE(3,"3");
		CASE_CARD_VALUE(4,"4");
		CASE_CARD_VALUE(5,"5");
		CASE_CARD_VALUE(6,"6");
		CASE_CARD_VALUE(7,"7");
		CASE_CARD_VALUE(8,"8");
		CASE_CARD_VALUE(9,"9");
		CASE_CARD_VALUE(BLOCK, "-block");
		CASE_CARD_VALUE(REVERSE, "-reverse");
		CASE_CARD_VALUE(PLUSTWO, "+2");
		CASE_CARD_VALUE(COLORPICK, "-colorpicker");
		CASE_CARD_VALUE(PLUSFOUR, "+4");

		default:
			out << '?';
			break;
	}

#undef CASE_CARD_VALUE

	return out;
}

void ConsoleUnoPlayer::listCards() {
	card_iterator it;

	int i = 1;
	for (it = hand.begin(); it != hand.end(); it++, i++) {
		out << i << ". ";
		//print card
		out << static_cast<UnoCard*>(*it);
		out << std::endl;
	}
	out << i << ". draw" << std::endl;
}

int ConsoleUnoPlayer::chooseCard() {
	out << "-Choose a card: ";

	int choose;
	bool valid = false;

	while (!valid) {
		in >> choose;

		valid = true;

		if (!in) {
			valid = false;
			in.clear();
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			out << "Choose a number between 1 and " << getCardCount()+1 << ":";
		}

		// range check - +1 because of draw
		if (choose < 1 || choose > getCardCount() + 1) {
			valid = false;
			out << "Invalid card number. Choose a valid card:";
		}

		/** @todo is valid move? */

	}

	return choose - 1;	// -1: index shift
}

UnoAction* ConsoleUnoPlayer::pickAction(UnoGame *game) {
	println("==Your turn");
	println("-Your cards:");
	listCards();
	int card_index = chooseCard();

	if (card_index == getCardCount()) {
		//it's a draw
		return NULL;
	} else {
		return hand[card_index];
	}
}

void ConsoleUnoPlayer::info(INFO_T type) {

}

}}} //namespace
