#ifndef SRC_UNO_GAME_DECK_H_
#define SRC_UNO_GAME_DECK_H_

#include "../action/card.h"

#include <deque>
//CARD_COLOR/VALUE, Card
using namespace ::Uno::Action;

namespace Uno { namespace Game {

class Deck {
protected:
    std::deque<Card *> deck;
    std::deque<Card *> played;

    static ptrdiff_t getrandom(ptrdiff_t i);
    virtual void shuffle(std::deque<Card *> &toShuffle);
    virtual void shufflePlayedIntoDeck();
public:
    Deck();
    virtual ~Deck();
    virtual void addCard(Card *card);
    virtual void shuffleDeck();
    virtual void playOutFirstCard();
    virtual void addCardToPlayed(Card *card);
    virtual Card* drawCard();

    CARD_COLOR last_played_color;
    CARD_VALUE last_played_value;
};

}} //namespace

#endif  // SRC_UNO_GAME_DECK_H_
