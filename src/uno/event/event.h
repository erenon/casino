#ifndef CSU_EVENT_H_
#define CSU_EVENT_H_

#include "../action/card.h"

namespace Casino { namespace Uno { namespace Player {
	class UnoPlayer;
}}} //namespace

namespace Casino { namespace Uno { namespace Action {
	class UnoCard;
}}} //namespace

namespace Casino { namespace Uno { namespace Event {

using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Action::UnoCard;

enum EVENT {
	EVENT_CARD_PLAYED,
	EVENT_DRAW_CARD,
	EVENT_COLORPICK,
	EVENT_GAME_START,
	EVENT_GAME_END
};

struct card_played {
	UnoPlayer* played_by;
	UnoCard* played_card;
};

struct draw_card {
	UnoPlayer* player;
	int card_count;
};

struct colorpick {
	UnoPlayer* picked_by;
	Casino::Uno::Action::CARD_COLOR color;
};

struct game_start {
	UnoCard* first_card;
};

struct game_end {
	UnoPlayer* winner;
};

}}} //namespace

#endif /* CSU_EVENT_H_ */
