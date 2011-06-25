#ifndef CSU_CARD_H_
#define CSU_CARD_H_

#include "../action/action.h"
//#include "../game/game.h"

namespace Casino { namespace Uno { namespace Action {
	class UnoAction;
}}} //namespace

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Action::UnoAction;
//using ::Casino::Uno::Game::UnoGame;

enum CARD_COLOR {
	CARD_COLOR_RED,
	CARD_COLOR_GREEN,
	CARD_COLOR_BLUE,
	CARD_COLOR_YELLOW,
	CARD_COLOR_BLACK
};

enum CARD_VALUE {
	CARD_VALUE_0,
	CARD_VALUE_1,
	CARD_VALUE_2,
	CARD_VALUE_3,
	CARD_VALUE_4,
	CARD_VALUE_5,
	CARD_VALUE_6,
	CARD_VALUE_7,
	CARD_VALUE_8,
	CARD_VALUE_9,
	CARD_VALUE_BLOCK,
	CARD_VALUE_REVERSE,
	CARD_VALUE_PLUSTWO,
	CARD_VALUE_COLORPICK,
	CARD_VALUE_PLUSFOUR
};

class UnoCard :public UnoAction
{
public:
	virtual bool isDisposeable() {
		return true;
	}
};

}}} //namespace

#endif /* CSU_CARD_H_ */
