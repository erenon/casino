#include "./card.h"

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
    std::string needed(color_string);

    m["red"] = CARD_COLOR_RED;
    m["green"] = CARD_COLOR_GREEN;
    m["blue"] = CARD_COLOR_BLUE;
    m["yellow"] = CARD_COLOR_YELLOW;
    m["black"] = CARD_COLOR_BLACK;


    found = m.find(needed);

    if (found == m.end()) {
        throw new std::invalid_argument("Invalid card color name");
    }

    return (*found).second;
}

CARD_VALUE Card::stringToValue(const char* value_string) {
    std::map<std::string, CARD_VALUE> m;
    std::map<std::string, CARD_VALUE>::iterator found;
    std::string needed(value_string);

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
    m["colorpick"] = CARD_VALUE_COLORPICK;
    m["+4"] = CARD_VALUE_PLUSFOUR;

    found = m.find(needed);

    if (found == m.end()) {
        throw new std::invalid_argument("Invalid card value name");
    }

    return (*found).second;
}

const char* Card::colorToString(CARD_COLOR needed_color) {
    std::map<CARD_COLOR, const char*> m;
    std::map<CARD_COLOR, const char*>::iterator found;

    m[CARD_COLOR_RED] = "red";
    m[CARD_COLOR_GREEN] = "green";
    m[CARD_COLOR_BLUE] = "blue";
    m[CARD_COLOR_YELLOW] = "yellow";
    m[CARD_COLOR_BLACK] = "black";

    found = m.find(needed_color);

    if (found == m.end()) {
        throw new std::invalid_argument("Invalid CARD_COLOR");
    }

    return (*found).second;
}

const char* Card::valueToString(CARD_VALUE needed_value) {
    std::map<CARD_VALUE, const char*> m;
    std::map<CARD_VALUE, const char*>::iterator found;

    m[CARD_VALUE_0] = "0";
    m[CARD_VALUE_1] = "1";
    m[CARD_VALUE_2] = "2";
    m[CARD_VALUE_3] = "3";
    m[CARD_VALUE_4] = "4";
    m[CARD_VALUE_5] = "5";
    m[CARD_VALUE_6] = "6";
    m[CARD_VALUE_7] = "7";
    m[CARD_VALUE_8] = "8";
    m[CARD_VALUE_9] = "9";
    m[CARD_VALUE_BLOCK] = "block";
    m[CARD_VALUE_REVERSE] = "reverse";
    m[CARD_VALUE_PLUSTWO] = "+2";
    m[CARD_VALUE_COLORPICK] = "colorpick";
    m[CARD_VALUE_PLUSFOUR] = "+4";

    found = m.find(needed_value);

    if (found == m.end()) {
        throw new std::invalid_argument("Invalid CARD_VALUE");
    }

    return (*found).second;
}

}}  // namespace
