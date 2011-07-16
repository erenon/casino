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
	out << std::endl << "==" << this->getName() << "'s turn" << std::endl;
	SimpleCard last_card = game->lastPlayedCard();
	out << "-Last card was: " << &last_card << std::endl;
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

	if (card_index != getCardCount()
	&& static_cast<UnoCard*>(picked)->getColor() == CARD_COLOR_BLACK) {
		CARD_COLOR new_color = chooseColor();
		static_cast<WildCard*>(picked)->setColor(new_color);
	}

	return picked;
}

void ConsoleUnoPlayer::notify(Event::EVENT event_type, void* event) {
	switch (event_type) {
	case Event::EVENT_GAME_START:
		println("==The Game has begun.");
		out << "-First card: "
			<< reinterpret_cast<Event::game_start*>(event)->first_card
			<< std::endl;
		break;

	case Event::EVENT_CARD_PLAYED:
	{
		Event::card_played* e = reinterpret_cast<Event::card_played*>(event);
		out << e->played_by->getName()
			<< " played "
			<< e->played_card
			<< std::endl;
	}
		break;

	case Event::EVENT_GAME_END:
	{
		Event::game_end* e = reinterpret_cast<Event::game_end*>(event);
		out << e->winner->getName()
			<< " wins"
			<< std::endl;
	}
		break;

	case Event::EVENT_COLORPICK:
	{
		Event::colorpick* e = reinterpret_cast<Event::colorpick*>(event);
		out << e->picked_by->getName()
			<< " picked color ";

		switch (e->color) {
		case CARD_COLOR_RED:
			out << "red";
			break;
		case CARD_COLOR_GREEN:
			out << "green";
			break;
		case CARD_COLOR_BLUE:
			out << "blue";
			break;
		case CARD_COLOR_YELLOW:
			out << "yellow";
			break;
		default:
			out << "??";
		}

		out << std::endl;
	}
		break;

	case Event::EVENT_DRAW_CARD:
	{
		Event::draw_card* e = reinterpret_cast<Event::draw_card*>(event);
		out << e->player->getName() << " draws " << e->card_count << " card";
		if (e->card_count > 1) {
			out << "s";
		}
		out << std::endl;

		break;
	}

	case Event::EVENT_GETS_BLOCKED:
	{
		Event::gets_blocked* e = reinterpret_cast<Event::gets_blocked*>(event);
		if (e->gets_blocked == this) {
			out << "You got blocked by " << e->blocked_by->getName() << std::endl;
		} else if (e->blocked_by == this) {
			out << "You blocked " << e->gets_blocked->getName() << std::endl;
		} else {
			out << e->blocked_by->getName() << " blocked " << e->gets_blocked->getName() << std::endl;
		}

		break;
	}

	case Event::EVENT_UNO_SAID:
	{
		Event::uno_said* e = reinterpret_cast<Event::uno_said*>(event);
		if (e->said_by == this) {
			if (e->type == Event::uno_said::GOOD) {

			} else if (e->type == Event::uno_said::BAD) {
				out << "You said uno at the wrong time. " \
					   "Say uno if you have only one card left " \
					   "by typing uno after the choosed card index" << std::endl;
			} else if (e->type == Event::uno_said::FORGOTTEN) {
				out << "You forgot to say uno " \
					   "Say uno if you have only one card left " \
					   "by typing uno after the choosed card index" << std::endl;
			}
		} else {
			if (e->type == Event::uno_said::GOOD) {
				out << e->said_by->getName()
					<< " is on UNO" << std::endl;
			} else if (e->type == Event::uno_said::BAD) {
				out << e->said_by->getName()
					<< " said uno too soon" << std::endl;
			} else if (e->type == Event::uno_said::FORGOTTEN) {
				out << e->said_by->getName()
					<< " forgot to say uno" << std::endl;
			}
		}

		break;
	}

	case Event::EVENT_PLAYER_JOINED:
	{
		Event::player_joined* e = reinterpret_cast<Event::player_joined*>(event);
		out << e->player->getName() << " joined to the game" << std::endl;
		break;
	}

	default:
		out << "[!] Unknown event... Event type id: "
			<< event_type << std::endl;
	}
}

}}} //namespace
