#ifndef SRC_UNO_EVENT_EVENT_H_
#define SRC_UNO_EVENT_EVENT_H_

#include "../action/card.h"

namespace Uno { namespace Player {
    class Player;
}}  // namespace

namespace Uno { namespace Action {
    class Card;
}}  // namespace

namespace Uno { namespace Event {

using ::Uno::Player::Player;
using ::Uno::Action::Card;

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
    ::Uno::Action::CARD_COLOR color;
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

}}  // namespace

#endif  // SRC_UNO_EVENT_EVENT_H_
