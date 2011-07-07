#ifndef CSU_BLOCK_CARD_H_
#define CSU_BLOCK_CARD_H_

#include "card.h"

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::UnoCard;
using ::Casino::Uno::Action::CARD_COLOR;
using ::Casino::Uno::Action::CARD_VALUE;

class BlockCard :public UnoCard
{
public:
	BlockCard(CARD_COLOR color)
		:UnoCard(color, CARD_VALUE_BLOCK)
	{}

	void takeAction(UnoGame* game) {
		game->blockNextPlayer();
	}
};

}}} //namespace

#endif /* BLOCK_CARD_H_ */
