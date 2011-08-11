#ifndef UNO_ACTION_BLOCK_CARD_H_
#define UNO_ACTION_BLOCK_CARD_H_

#include "card.h"

namespace Uno { namespace Action {

using ::Uno::Action::Card;
using ::Uno::Action::CARD_COLOR;
using ::Uno::Action::CARD_VALUE;

class BlockCard :public Card
{
public:
	BlockCard(CARD_COLOR color)
		:Card(color, CARD_VALUE_BLOCK)
	{}

	void takeAction(Game* game) {
		game->blockNextPlayer();
	}
};

}} //namespace

#endif /* BLOCK_CARD_H_ */
