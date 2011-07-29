#ifndef CSU_EVENT_H_
#define CSU_EVENT_H_

#include "../action/card.h"

namespace Casino { namespace Uno { namespace Player {
	class UnoPlayer;
}}} //namespace

namespace Casino { namespace Uno { namespace Action {
	class Card;
}}} //namespace

namespace Casino { namespace Uno { namespace Event {

using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Action::Card;

enum EVENT {
	EVENT_CARD_PLAYED,
	EVENT_DRAW_CARD,
	EVENT_COLORPICK,
	EVENT_GAME_START,
	EVENT_GAME_END,
	EVENT_UNO_SAID,
	EVENT_GETS_BLOCKED,
	EVENT_PLAYER_JOINED
};

struct card_played {
	UnoPlayer* played_by;
	Card* played_card;
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
	Card* first_card;
};

struct game_end {
	UnoPlayer* winner;
};

struct uno_said {
	enum TYPE {
		GOOD,
		BAD,
		FORGOTTEN
	};
	UnoPlayer* said_by;
	TYPE type;
};

struct gets_blocked {
	UnoPlayer* gets_blocked;
	UnoPlayer* blocked_by;
};

struct player_joined {
	UnoPlayer* player;
};

}}} //namespace

#endif /* CSU_EVENT_H_ */
