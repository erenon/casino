#ifndef UNO_ACTION_REVERSE_CARD_H_
#define UNO_ACTION_REVERSE_CARD_H_

#include "card.h"

namespace Uno { namespace Action {

using ::Uno::Action::Card;
using ::Uno::Action::CARD_COLOR;
using ::Uno::Action::CARD_VALUE;

class ReverseCard :public Card
{
public:
    ReverseCard(CARD_COLOR color);
    void takeAction(Game* game);
};

}} //namespace

#endif /* UNO_ACTION_REVERSE_CARD_H_ */
