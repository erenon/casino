#ifndef SRC_UNO_ACTION_PLUSFOUR_CARD_H_
#define SRC_UNO_ACTION_PLUSFOUR_CARD_H_

#include "./wild_card.h"

namespace Uno { namespace Action {

using ::Uno::Action::WildCard;
using ::Uno::Action::CARD_COLOR;
using ::Uno::Action::CARD_VALUE;

class PlusfourCard :public WildCard {

 public:
    PlusfourCard();
    void takeAction(Game* game);
};

}}  // namespace

#endif  // SRC_UNO_ACTION_PLUSFOUR_CARD_H_
