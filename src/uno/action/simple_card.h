#ifndef CSU_SIMPLE_CARD_H_
#define CSU_SIMPLE_CARD_H_

#include "card.h"

namespace Casino { namespace Uno { namespace Game {
	class Game;
}}} //namespace

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::Card;
using ::Casino::Uno::Action::CARD_COLOR;
using ::Casino::Uno::Action::CARD_VALUE;

class SimpleCard :public Card
{
public:
	SimpleCard(CARD_COLOR color, CARD_VALUE value)
		:Card(color, value)
	{}

	virtual void takeAction(Game* game) {}
};

}}} //namespace

#endif /* CSU_SIMPLE_CARD_H_ */
