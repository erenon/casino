#ifndef UNO_ACTION_PLUSFOUR_CARD_H_
#define UNO_ACTION_PLUSFOUR_CARD_H_

#include "wild_card.h"

namespace Uno { namespace Action {

using ::Uno::Action::WildCard;
using ::Uno::Action::CARD_COLOR;
using ::Uno::Action::CARD_VALUE;

class PlusfourCard :public WildCard
{
public:
    PlusfourCard();
    void takeAction(Game* game);
};

}} //namespace

#endif /* UNO_ACTION_PLUSFOUR_CARD_H_ */
