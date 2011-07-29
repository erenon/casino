#ifndef CSU_BLOCK_CARD_H_
#define CSU_BLOCK_CARD_H_

#include "card.h"

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::Card;
using ::Casino::Uno::Action::CARD_COLOR;
using ::Casino::Uno::Action::CARD_VALUE;

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

}}} //namespace

#endif /* BLOCK_CARD_H_ */
