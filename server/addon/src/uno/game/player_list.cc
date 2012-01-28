#include "./player_list.h"

#include "../player/player.h"

#include <list>

namespace Uno { namespace Game {

using ::Uno::Player::Player;

PlayerList::PlayerList()
    :turn_direction_normal(true),
     prev_player(NULL) {
    current_player = players.end();
}

void PlayerList::joinPlayer(Player* player) {
    players.push_back(player);

    // init current player on the first join
    if (current_player == players.end()) {
    	current_player = players.begin();
    }
}

int PlayerList::size() {
    return players.size();
}

PlayerList::player_iterator PlayerList::determineNextPlayer() {
    player_iterator next_player = current_player;

    if (turn_direction_normal) {
        next_player++;

        if (next_player == players.end()) {
            // current player is at the end of the list
            // next player is the first player
            next_player = players.begin();
        }
    } else {
        if (next_player == players.begin()) {
            // current player is at the beginning of the list
            // prev player is at the end
            next_player = players.end();
            next_player--;
        } else {
            next_player--;
        }
    }

    return next_player;
}

/**
 * Returns the next player in turn.
 *
 * Doesn't take blocking into account.
 */
Player *PlayerList::getNextPlayer() {
    return *determineNextPlayer();
}

/**
 * Returns the player previously played.
 *
 * Just after the turn direction switch, it returns
 * the last player played, and NOT the one before
 * the current player in turn order.
 * This may be confusing compared to the dynamic nature of
 * getNextPlayer()
 *
 * TODO revise this.
 */
Player *PlayerList::getPreviousPlayer() {
    return prev_player;
}

Player *PlayerList::getCurrentPlayer() {
    return *current_player;
}

Player *PlayerList::next() {
    prev_player = *current_player;
    current_player = determineNextPlayer();
    return *current_player;
}

void PlayerList::notifyAll(Event::EVENT event_type, void* event) {
    player_iterator it;

    for (it = players.begin(); it != players.end(); it++) {
        (*it)->notify(event_type, event);
    }
}

void PlayerList::notifyOthers(Event::EVENT event_type, void* event, Player* player) {
    player_iterator it;

    for (it = players.begin(); it != players.end(); it++) {
        if (*it != player) {
            (*it)->notify(event_type, event);
        }
    }
}

void PlayerList::reset() {
    prev_player = NULL;
    current_player = players.begin();
}

void PlayerList::reverseTurn() {
    turn_direction_normal = !turn_direction_normal;
}

}}  // namespace
