#ifndef CSU_SIMPLE_CARD_H_
#define CSU_SIMPLE_CARD_H_

#include "card.h";

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::Card;
using ::Casino::Uno::Action::CARD_COLOR;
using ::Casino::Uno::Action::CARD_VALUE;

class SimpleCard :public Card
{
private:
	CARD_COLOR color;
	CARD_VALUE value;
public:
	SimpleCard(CARD_COLOR color, CARD_VALUE value)
		:color(color),
		 value(value)
	{}

	virtual void takeAction(UnoGame* game) {}
};

}}} //namespace

#endif /* CSU_SIMPLE_CARD_H_ */
