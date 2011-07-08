#ifndef CSU_WILD_CARD_H_
#define CSU_WILD_CARD_H_

#include "card.h"

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::UnoCard;
using ::Casino::Uno::Action::CARD_COLOR;
using ::Casino::Uno::Action::CARD_VALUE;

class WildCard :public UnoCard
{
protected:
	CARD_COLOR choosen_color;
public:
	void setColor(CARD_COLOR color);
	void takeAction(UnoGame* game);
};

}}} //namespace

#endif /* CSU_WILD_CARD_H_ */
