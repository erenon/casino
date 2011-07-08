#include "console_player.h"
#include "../game/game.h"
#include <iostream>
#include <limits> //for istream ignore
#include <cstring>
#include <string>

namespace Casino { namespace Uno { namespace Player {

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
		//out << 'R';
		out << "\E[37;41m\033[1m";
		break;
	case CARD_COLOR_GREEN:
		//out << 'G';
		out << "\E[37;42m\033[1m";
		break;
	case CARD_COLOR_BLUE:
		//out << 'B';
		out << "\E[37;44m\033[1m";
		break;
	case CARD_COLOR_YELLOW:
		//out << 'Y';
		out << "\E[38;5;11m\033[1m";
		break;
	case CARD_COLOR_BLACK:
		out << "\E[37;40m\033[1m";
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
		CASE_CARD_VALUE(BLOCK, "block");
		CASE_CARD_VALUE(REVERSE, "reverse");
		CASE_CARD_VALUE(PLUSTWO, "+2");
		CASE_CARD_VALUE(COLORPICK, "colorpicker");
		CASE_CARD_VALUE(PLUSFOUR, "+4");

		default:
			out << '?';
			break;
	}

#undef CASE_CARD_VALUE

	out << "\033[0m\E[0m";

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
	int choose;
	bool valid = false;

	while (!valid) {
		in >> choose;

		if (!in) {
			in.clear();
			out << "Choose a number between 1 and " << getCardCount()+1 << ":";
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		// range check - +1 because of draw
		if (choose < 1 || choose > getCardCount() + 1) {
			valid = false;
			out << "Invalid card number. Choose a valid card:";
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		valid = true;

		// check uno
		char uno[4];
		uno[0] = in.peek();
		if (uno[0] == ' ') {
			in.ignore(1, ' ');
			in.get(uno, 4, '\n');

			uno[3] = '\0';
			if (strcmp(uno, "uno") == 0) {
				setUnoFlag(true);
			}
		}

		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return choose - 1;	// -1: index shift
}

CARD_COLOR ConsoleUnoPlayer::chooseColor() {
	out << "-Choose a color (red/green/blue/yellow): ";
	char color_first_letter;
	CARD_COLOR color = CARD_COLOR_BLACK;


	while (color == CARD_COLOR_BLACK) {
		color_first_letter = in.peek();

		switch (color_first_letter) {
			case 'r':
				color = CARD_COLOR_RED;
				break;
			case 'g':
				color = CARD_COLOR_GREEN;
				break;
			case 'b':
				color = CARD_COLOR_BLUE;
				break;
			case 'y':
				color = CARD_COLOR_YELLOW;
				break;
			default:
				out << "-Invalid color (red/green/blue/yellow): ";
				in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				break;
		}
	}

	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return color;
}

UnoAction* ConsoleUnoPlayer::pickAction(UnoGame *game) {
	println("==Your turn");
	println("-Your cards:");
	listCards();

	out << "-Choose a card: ";
	int card_index;
	UnoAction* picked;
	bool valid = false;
	while (!valid) {
		card_index = chooseCard();
		if (card_index == getCardCount()) {
			//it's a draw
			picked = game->getDrawAction();
		} else {
			picked = hand[card_index];
		}

		std::string message = "";
		valid = game->isValidMove(picked, message);
		if (!valid) {
			out << "Invalid move. " << message <<": ";
		}
	}

	/** @todo add color picking */
	if (card_index != getCardCount()
	&& static_cast<UnoCard*>(picked)->getColor() == CARD_COLOR_BLACK) {
		CARD_COLOR new_color = chooseColor();
		static_cast<WildCard*>(picked)->setColor(new_color);
	}

	return picked;
}

void ConsoleUnoPlayer::info(INFO_T type) {

}

}}} //namespace
