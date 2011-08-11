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
	ReverseCard(CARD_COLOR color)
		:Card(color, CARD_VALUE_REVERSE)
	{}

	void takeAction(Game* game) {
		game->reverseTurn();
	}
};

}} //namespace

#endif /* UNO_ACTION_REVERSE_CARD_H_ */
