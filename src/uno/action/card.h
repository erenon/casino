#ifndef SRC_UNO_ACTION_CARD_H_
#define SRC_UNO_ACTION_CARD_H_

#include "./action.h"

namespace Uno { namespace Action {
    class Action;
}}  // namespace

namespace Uno { namespace Action {

using ::Uno::Action::Action;

enum CARD_COLOR {
    CARD_COLOR_RED,
    CARD_COLOR_GREEN,
    CARD_COLOR_BLUE,
    CARD_COLOR_YELLOW,
    CARD_COLOR_BLACK
};

enum CARD_VALUE {
    CARD_VALUE_0,
    CARD_VALUE_1,
    CARD_VALUE_2,
    CARD_VALUE_3,
    CARD_VALUE_4,
    CARD_VALUE_5,
    CARD_VALUE_6,
    CARD_VALUE_7,
    CARD_VALUE_8,
    CARD_VALUE_9,
    CARD_VALUE_BLOCK,
    CARD_VALUE_REVERSE,
    CARD_VALUE_PLUSTWO,
    CARD_VALUE_COLORPICK,
    CARD_VALUE_PLUSFOUR
};

class Card :public Action {

protected:
    CARD_COLOR color;
    CARD_VALUE value;
public:
    Card();
    Card(CARD_COLOR color, CARD_VALUE value);

    virtual bool isDisposeable();
    virtual CARD_COLOR getColor();
    virtual CARD_VALUE getValue();

    static CARD_COLOR stringToColor(const char* color_string);
    static CARD_VALUE stringToValue(const char* value_string);
    static const char* colorToString(CARD_COLOR needed_color);
    static const char* valueToString(CARD_VALUE needed_value);
};

}}  // namespace

#endif  // SRC_UNO_ACTION_CARD_H_
