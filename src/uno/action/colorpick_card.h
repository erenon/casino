#ifndef CSU_COLORPICK_CARD_H_
#define CSU_COLORPICK_CARD_H_

#include "card.h";

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::Card;
using ::Casino::Uno::Action::CARD_COLOR;
using ::Casino::Uno::Action::CARD_VALUE;

class ColorpickCard :public Card
{
private:
	CARD_COLOR color;
	CARD_VALUE value;
public:
	ColorpickCard()
	{
		color = CARD_COLOR_BLACK;
		value = CARD_VALUE_COLORPICK;
	}

	void takeAction(UnoGame* game) {}
};

}}} //namespace

#endif /* CSU_COLORPICK_CARD_H_ */
