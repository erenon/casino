#include "./game.h"

#include <stdexcept>

namespace Uno { namespace Game {

Game::Game(int max_player_count)
    :max_player_count(max_player_count),
     last_played_player(NULL),
     current_penalty(0) {}

//
// PLAYERS
//

void Game::joinPlayer(Player *player) {
    if (players.size() >= max_player_count) {
        throw std::overflow_error("Game is full");
    }

    players.joinPlayer(player);


    {   // notify about joined player
        Event::player_joined event;
        event.player = player;
        players.notifyOthers(
            Event::EVENT_PLAYER_JOINED,
            reinterpret_cast<void*>(&event),
            player
        );
    }
}

int Game::getPlayerCount() {
    return players.size();
}

//
// PENALTY
//

bool Game::isPenalty() {
    return (current_penalty > 0);
}

void Game::increasePenality(int addition) {
    current_penalty += addition;
}

void Game::dealPenality(Player* player) {
    for (int i = 0; i < current_penalty; i++) {
        dealCard(player);
    }

    current_penalty = 0;
}

void Game::dealCard(Player* player) {
    Card* top_card = deck.drawCard();
    player->addCard(top_card);
}

//
// LAST PLAYED PLAYER
//

void Game::registerLastPlayedPlayer(Player* player) {
    last_played_player = player;
}

Player* Game::getLastPlayedPlayer() {
    return last_played_player;
}

//
// CARD ACTIONS
//

void Game::blockNextPlayer() {
    players.getNextPlayer()->block();

    {
        Event::gets_blocked event;
        event.gets_blocked = players.getNextPlayer();
        event.blocked_by = players.getCurrentPlayer();

        players.notifyAll(
            Event::EVENT_GETS_BLOCKED,
            reinterpret_cast<void*>(&event)
        );
    }
}

void Game::reverseTurn() {
    players.reverseTurn();
}

void Game::drawCards() {
    Player *player = players.getCurrentPlayer();
    // player draws the current penalty or a single card
    int card_count = (isPenalty()) ? current_penalty : 1;

    if (isPenalty()) {
        dealPenality(player);
    } else {
        dealCard(player);
    }

    {   // notify about the card draw
        Event::draw_card event;
        event.player = players.getCurrentPlayer();
        event.card_count = card_count;
        players.notifyOthers(
            Event::EVENT_DRAW_CARD,
            reinterpret_cast<void*>(&event),
            players.getCurrentPlayer()
        );
    }
}

void Game::setLastColor(CARD_COLOR color) {
    deck.last_played_color = color;

    Event::colorpick event;
    event.picked_by = players.getCurrentPlayer();
    event.color = color;
    players.notifyOthers(
        Event::EVENT_COLORPICK,
        reinterpret_cast<void*>(&event),
        players.getCurrentPlayer()
    );
}

}}  // namespace
