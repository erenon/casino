#include "card.h"

#include <map>
#include <string>
#include <stdexcept>

namespace Uno { namespace Action {

Card::Card() {}

Card::Card(CARD_COLOR color, CARD_VALUE value)
	:color(color),
	 value(value)
{}

bool Card::isDisposeable() {
	return true;
}

CARD_COLOR Card::getColor() {
	return color;
}

CARD_VALUE Card::getValue() {
	return value;
}

CARD_COLOR Card::stringToColor(const char* color_string) {
	std::map<std::string, CARD_COLOR> m;
	std::map<std::string, CARD_COLOR>::iterator found;

	m["red"] = CARD_COLOR_RED;
	m["green"] = CARD_COLOR_GREEN;
	m["blue"] = CARD_COLOR_BLUE;
	m["yellow"] = CARD_COLOR_YELLOW;
	m["black"] = CARD_COLOR_BLACK;

	std::string needed(color_string);
	found = m.find(needed);

	if (found == m.end()) {
		throw new std::invalid_argument("Invalid card color name");
	}

	return (*found).second;
}

CARD_VALUE Card::stringToValue(const char* value_string) {
	std::map<std::string, CARD_VALUE> m;
	std::map<std::string, CARD_VALUE>::iterator found;

	m["0"] = CARD_VALUE_0;
	m["1"] = CARD_VALUE_1;
	m["2"] = CARD_VALUE_2;
	m["3"] = CARD_VALUE_3;
	m["4"] = CARD_VALUE_4;
	m["5"] = CARD_VALUE_5;
	m["6"] = CARD_VALUE_6;
	m["7"] = CARD_VALUE_7;
	m["8"] = CARD_VALUE_8;
	m["9"] = CARD_VALUE_9;
	m["block"] = CARD_VALUE_BLOCK;
	m["reverse"] = CARD_VALUE_REVERSE;
	m["+2"] = CARD_VALUE_PLUSTWO;
	m["colorpicker"] = CARD_VALUE_COLORPICK;
	m["+4"] = CARD_VALUE_PLUSFOUR;

	std::string needed(value_string);
	found = m.find(needed);

	if (found == m.end()) {
		throw new std::invalid_argument("Invalid card value name");
	}

	return (*found).second;
}

}} //namespace
