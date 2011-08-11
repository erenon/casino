#include "./deck.h"

#include "../action/card.h"
#include "../action/simple_card.h"
#include "../action/block_card.h"
#include "../action/reverse_card.h"
#include "../action/plustwo_card.h"
#include "../action/plusfour_card.h"
#include "../action/colorpick_card.h"

#include <stdexcept>
#include <deque>

// shuffle:
#include <algorithm>
#include <ctime>
#include <cstdlib>

namespace Uno { namespace Game {

using ::Uno::Action::Card;

Deck::Deck() {
    // initialize cards
    CARD_COLOR colors[] = {
            CARD_COLOR_RED,
            CARD_COLOR_GREEN,
            CARD_COLOR_BLUE,
            CARD_COLOR_YELLOW
    };

    const int color_count = 4;

    CARD_VALUE values[] = {
        CARD_VALUE_1,
        CARD_VALUE_2,
        CARD_VALUE_3,
        CARD_VALUE_4,
        CARD_VALUE_5,
        CARD_VALUE_6,
        CARD_VALUE_7,
        CARD_VALUE_8,
        CARD_VALUE_9
    };

    const int value_count = 9;

    for (int color = 0; color < color_count; color++) {
        // add 0
        addCard(new SimpleCard(colors[color], CARD_VALUE_0));

        // add two card of a kind
        for (int i = 0; i < 2; i++) {

            // add 1-9
            for (int value = 0; value < value_count; value++) {
                addCard(new SimpleCard(colors[color], values[value]));
            }

            addCard(new BlockCard(colors[color]));
            addCard(new ReverseCard(colors[color]));
            addCard(new PlustwoCard(colors[color]));
        }
    }

    const int black_count = 4;

    for (int i = 0; i < black_count; i++) {
        addCard(new PlusfourCard());
        addCard(new ColorpickCard());
    }
}

Deck::~Deck() {
    // delete cards
    std::deque<Card *>::iterator card;

    for (card = deck.begin(); card != deck.end(); card++) {
        delete *card;
    }
    for (card = played.begin(); card != played.end(); card++) {
        delete *card;
    }
}

ptrdiff_t Deck::getrandom(ptrdiff_t i) {
    return rand() % i;
}

void Deck::shuffle(std::deque<Card *> &toShuffle) {
    srand( unsigned( time(NULL)));
    std::random_shuffle(toShuffle.begin(), toShuffle.end(), getrandom);
}

void Deck::shufflePlayedIntoDeck() {
    shuffle(played);

    std::deque<Card *>::iterator it;
    for (it = played.begin(); it != played.end(); it++) {
        addCard(*it);
    }

    played.clear();
}

void Deck::addCard(Card *card) {
    deck.push_back(card);
}

void Deck::shuffleDeck() {
    shuffle(deck);
}

void Deck::playOutFirstCard() {
    Card* top_card;
    bool card_ok = false;

    while (!card_ok) {
        top_card = drawCard();
        CARD_COLOR color = top_card->getColor();
        CARD_VALUE value = top_card->getValue();

        if (
            color != CARD_COLOR_BLACK
        &&  value != CARD_VALUE_BLOCK
        &&  value != CARD_VALUE_PLUSTWO
        &&  value != CARD_VALUE_REVERSE
        ) {
            // card ok, play out
            last_played_color = top_card->getColor();
            last_played_value = top_card->getValue();
            addCardToPlayed(top_card);
            card_ok = true;
        } else {
            // !SimpleCard, take it back
            addCard(top_card);
        }
    }
}

void Deck::addCardToPlayed(Card *card) {
    played.push_front(card);
}

Card* Deck::drawCard() {
    if (deck.size() == 0) {
        if (played.size() > 0) {
            shufflePlayedIntoDeck();
        } else {
            throw std::length_error("No card in deck");
        }
    }

    Card* top_card = deck.front();
    deck.pop_front();
    return top_card;
}

}}  // namespace
