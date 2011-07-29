#ifndef CSU_PLUSFOUR_CARD_H_
#define CSU_PLUSFOUR_CARD_H_

#include "wild_card.h"

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::WildCard;
using ::Casino::Uno::Action::CARD_COLOR;
using ::Casino::Uno::Action::CARD_VALUE;

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

}}} //namespace

#endif /* CSU_PLUSFOUR_CARD_H_ */
