#include "async_game.h"

#include "deck.h"
#include "../event/event.h"
#include "../action/simple_card.h"

#include <string>
#include <stdexcept>

namespace Uno { namespace Game {

namespace Event = ::Uno::Event;
using ::Uno::Action::SimpleCard;

AsyncGame::AsyncGame(int max_player_count)
    :Uno::Game::Game(max_player_count)
{

}

void AsyncGame::start() {
    // prepare deck
    deck.shuffleDeck();
    deck.playOutFirstCard();

    // deal initial hands
    std::list<Player *>::iterator player;
    for (int card_idx = 0; card_idx < config.initial_hand_size; card_idx++) {
        players.reset();
        for (int i = 0; i < players.size(); i++, players.next()) {
            players.getCurrentPlayer()->addCard(deck.drawCard());

            {
                Event::draw_card event;
                event.card_count = 1;
                event.player = players.getCurrentPlayer();
                players.notifyOthers(
                    Event::EVENT_DRAW_CARD,
                    reinterpret_cast<void*>(&event),
                    players.getCurrentPlayer()
                );
            }
        }
    }

    {   // send game start event
        Event::game_start event;
        SimpleCard first_card(
            deck.last_played_color,
            deck.last_played_value
        );
        event.first_card = &first_card;
        players.notifyAll(
            Event::EVENT_GAME_START,
            reinterpret_cast<void*>(&event)
        );
    }

    {   // start the first turn
        players.reset();
        Event::players_turn event;
        event.player = players.getCurrentPlayer();
        players.notifyAll(
            Event::EVENT_PLAYERS_TURN,
            reinterpret_cast<void*>(&event)
        );
    }
}

/**
 * @todo use enum status instead of string,
 * tweak takeAction to it after
 */
bool AsyncGame::isValidMove(Player* player, Action* action, std::string &message) {
    if (action == &draw_action && player == players.getCurrentPlayer()) {
        return true;
    }

    Card *card = static_cast<Card*>(action);

    // current player or same card
    if (
        deck.last_played_color == card->getColor()
    &&  deck.last_played_value == card->getValue()
    ) {
        return true;
    } else if (player != players.getCurrentPlayer()) {
        message = "Not your turn";
        return false;
    }

    if (isPenalty()) {
        if (deck.last_played_value == CARD_VALUE_PLUSFOUR) {
            if (card->getValue() == CARD_VALUE_PLUSFOUR) {
                return true;
            } else {
                message = "Must play +4 or draw";
                return false;
            }
        } else {
            if (
                card->getValue() == CARD_VALUE_PLUSFOUR ||
                card->getValue() == CARD_VALUE_PLUSTWO
            ) {
                return true;
            } else {
                message = "Must play +4 or +2 or draw";
                return false;
            }
        }
    } else {
        if (card->getColor() == CARD_COLOR_BLACK) {
            return true;
        }

        if (deck.last_played_color == card->getColor()) {
            return true;
        }

        if (deck.last_played_value == card->getValue()) {
            return true;
        }

        message = "The color or the figure must match";
        return false;
    }
}

void AsyncGame::takeAction(Player* player, Action* action) {
    std::string message;
    bool is_valid = false;
    is_valid = isValidMove(player, action, message);

    if (!is_valid) {
        throw std::invalid_argument(message.c_str());
    }

    if (action->isDisposeable()) {
        Card* played_card = static_cast<Card*>(action);

        player->removeCard(played_card);

        deck.last_played_color = played_card->getColor();
        deck.last_played_value = played_card->getValue();
        deck.addCardToPlayed(played_card);

        { //notify about played card
            Event::card_played event;
            SimpleCard played_card(
                deck.last_played_color,
                deck.last_played_value
            );
            event.played_card = &played_card;
            event.played_by = player;
            players.notifyOthers(
                Event::EVENT_CARD_PLAYED,
                reinterpret_cast<void*>(&event),
                player
            );
        }
    }

    // call actions action
    action->takeAction(this);

    // check for forgotten uno
    /** @todo implement this */
    //checkUno();

    // determine next player
    Player* next_player;
    bool next_player_found = false;

    while (!next_player_found) {
        players.next();
        next_player = players.getCurrentPlayer();
        if (next_player->isBlocked() == true) {
            next_player->unblock();
        } else {
            next_player_found = true;
        }
    }

    if (next_player->getCardCount() == 0) {
        // this player wins
        Event::game_end event;
        event.winner = players.getCurrentPlayer();
        players.notifyAll(
            Event::EVENT_GAME_END,
            reinterpret_cast<void*>(&event)
        );
    }

    {   // notify about the next player
        Event::players_turn event;
        event.player = players.getCurrentPlayer();
        players.notifyAll(
            Event::EVENT_PLAYERS_TURN,
            reinterpret_cast<void*>(&event)
        );
    }
}

void AsyncGame::takeDraw(Player* player) {
    takeAction(player, &draw_action);
}

}} //namespace
