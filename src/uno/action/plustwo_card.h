#ifndef CSU_PLUSTWO_CARD_H_
#define CSU_PLUSTWO_CARD_H_

#include "card.h"

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::Card;
using ::Casino::Uno::Action::CARD_COLOR;
using ::Casino::Uno::Action::CARD_VALUE;

class PlustwoCard :public Card
{
public:
	PlustwoCard(CARD_COLOR color)
		:Card(color, CARD_VALUE_PLUSTWO)
	{}

	void takeAction(Game* game) {
		game->increasePenality(2);
	}
};

}}} //namespace

#endif /* CSU_PLUSTWO_CARD_H_ */
