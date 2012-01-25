#ifndef SRC_UNO_ACTION_REVERSE_CARD_H_
#define SRC_UNO_ACTION_REVERSE_CARD_H_

#include "./card.h"

namespace Uno { namespace Action {

using ::Uno::Action::Card;
using ::Uno::Action::CARD_COLOR;
using ::Uno::Action::CARD_VALUE;

class ReverseCard :public Card {

 public:
    explicit ReverseCard(CARD_COLOR color);
    void takeAction(Game* game);
};

}}  // namespace

#endif  // SRC_UNO_ACTION_REVERSE_CARD_H_
