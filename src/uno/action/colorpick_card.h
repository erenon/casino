#ifndef SRC_UNO_ACTION_COLORPICK_CARD_H_
#define SRC_UNO_ACTION_COLORPICK_CARD_H_

#include "./wild_card.h"

namespace Uno { namespace Action {

using ::Uno::Action::WildCard;
using ::Uno::Action::CARD_COLOR;
using ::Uno::Action::CARD_VALUE;

class ColorpickCard :public WildCard {

 public:
    ColorpickCard() {
        color = CARD_COLOR_BLACK;
        value = CARD_VALUE_COLORPICK;
    }

    void takeAction(Game* game) {
        WildCard::takeAction(game);
    }
};

}}  // namespace

#endif  // SRC_UNO_ACTION_COLORPICK_CARD_H_
