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
	PlusfourCard()
	{
		color = CARD_COLOR_BLACK;
		value = CARD_VALUE_PLUSFOUR;
	}

	void takeAction(Game* game) {
		game->increasePenality(4);
		WildCard::takeAction(game);
	}
};

}} //namespace

#endif /* UNO_ACTION_PLUSFOUR_CARD_H_ */
