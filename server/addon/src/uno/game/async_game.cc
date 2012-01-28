#include "./async_game.h"

#include <string>
#include <stdexcept>

#include "./deck.h"
#include "../event/event.h"
#include "../action/simple_card.h"

namespace Uno { namespace Game {

namespace Event = ::Uno::Event;
using ::Uno::Action::SimpleCard;

AsyncGame::AsyncGame(int max_player_count)
    :Uno::Game::Game(max_player_count) {}

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

    /** @todo add disposeable check here */
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

void AsyncGame::checkUno() {
    Player* player = getLastPlayedPlayer();

    if (player != NULL) {
        bool uno = player->getUnoFlag();

        if ((player->getCardCount() == 1 && uno == false)
        ||  (player->getCardCount() != 1 && uno != false)) {
            // no uno said or not needed uno said
            int penalty = config.wrong_uno_penalty;

            for (int i = 0; i < penalty; i++) {
                player->addCard(deck.drawCard());
            }
        }

        // reset uno flag
        if (uno) {
            player->setUnoFlag(false);
        }
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

        { // notify about played card
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

    registerLastPlayedPlayer(player);

    // check for forgotten uno
    checkUno();

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

    // win or next player
    if (next_player->getCardCount() == 0 && !isPenalty()) {
        // this player wins
        Event::game_end event;
        event.winner = players.getCurrentPlayer();
        players.notifyAll(
            Event::EVENT_GAME_END,
            reinterpret_cast<void*>(&event)
        );
    } else {
        // notify about the next player
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

void AsyncGame::sayUno(Player* player) {
    Event::uno_said event;
    event.said_by = player;

    players.notifyOthers(
        Event::EVENT_UNO_SAID,
        reinterpret_cast<void*>(&event),
        player
    );
}

}}  // namespace
