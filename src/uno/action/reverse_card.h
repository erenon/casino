#ifndef CSU_REVERSE_CARD_H_
#define CSU_REVERSE_CARD_H_

#include "card.h"

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::UnoCard;
using ::Casino::Uno::Action::CARD_COLOR;
using ::Casino::Uno::Action::CARD_VALUE;

class ReverseCard :public UnoCard
{
public:
	ReverseCard(CARD_COLOR color)
		:UnoCard(color, CARD_VALUE_REVERSE)
	{}

	void takeAction(UnoGame* game) {
		game->reverseTurn();
	}
};

}}} //namespace

#endif /* CSU_REVERSE_CARD_H_ */
