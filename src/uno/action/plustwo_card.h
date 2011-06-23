#ifndef CSU_PLUSTWO_CARD_H_
#define CSU_PLUSTWO_CARD_H_

#include "card.h";

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::Card;
using ::Casino::Uno::Action::CARD_COLOR;
using ::Casino::Uno::Action::CARD_VALUE;

class PlustwoCard :public Card
{
private:
	CARD_COLOR color;
	CARD_VALUE value;
public:
	PlustwoCard(CARD_COLOR color)
		:color(color)
	{
		value = CARD_VALUE_PLUSTWO;
	}

	void takeAction(UnoGame* game) {
		game->increasePenality(2);
	}
};

}}} //namespace

#endif /* CSU_PLUSTWO_CARD_H_ */
