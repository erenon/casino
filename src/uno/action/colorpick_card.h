#ifndef CSU_COLORPICK_CARD_H_
#define CSU_COLORPICK_CARD_H_

#include "wild_card.h"

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::WildCard;
using ::Casino::Uno::Action::CARD_COLOR;
using ::Casino::Uno::Action::CARD_VALUE;

class ColorpickCard :public WildCard
{
public:
	ColorpickCard()
	{
		color = CARD_COLOR_BLACK;
		value = CARD_VALUE_COLORPICK;
	}

	void takeAction(Game* game) {
		WildCard::takeAction(game);
	}
};

}}} //namespace

#endif /* CSU_COLORPICK_CARD_H_ */
