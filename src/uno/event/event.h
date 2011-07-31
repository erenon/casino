#ifndef CSU_EVENT_H_
#define CSU_EVENT_H_

#include "../action/card.h"

namespace Casino { namespace Uno { namespace Player {
	class Player;
}}} //namespace

namespace Casino { namespace Uno { namespace Action {
	class Card;
}}} //namespace

namespace Casino { namespace Uno { namespace Event {

using ::Casino::Uno::Player::Player;
using ::Casino::Uno::Action::Card;

enum EVENT {
	EVENT_CARD_PLAYED,
	EVENT_DRAW_CARD,
	EVENT_COLORPICK,
	EVENT_GAME_START,
	EVENT_GAME_END,
	EVENT_UNO_SAID,
	EVENT_GETS_BLOCKED,
	EVENT_PLAYER_JOINED,
	EVENT_PLAYERS_TURN
};

struct card_played {
	Player* played_by;
	Card* played_card;
};

struct draw_card {
	Player* player;
	int card_count;
};

struct colorpick {
	Player* picked_by;
	Casino::Uno::Action::CARD_COLOR color;
};

struct game_start {
	Card* first_card;
};

struct game_end {
	Player* winner;
};

struct uno_said {
	enum TYPE {
		GOOD,
		BAD,
		FORGOTTEN
	};
	Player* said_by;
	TYPE type;
};

struct gets_blocked {
	Player* gets_blocked;
	Player* blocked_by;
};

struct player_joined {
	Player* player;
};

struct players_turn {
	Player* player;
};

}}} //namespace

#endif /* CSU_EVENT_H_ */
