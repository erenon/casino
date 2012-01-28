#ifndef SRC_UNO_GAME_DECK_H_
#define SRC_UNO_GAME_DECK_H_

#include <deque>

#include "../action/card.h"

namespace Uno { namespace Game {

// CARD_COLOR/VALUE, Card
using namespace ::Uno::Action;

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
    virtual void addCard(Card *card);    /**< TODO hide this */
    virtual void shuffleDeck();
    virtual void playOutFirstCard();    /**< TODO rename: Out doesn't needed*/
    virtual void addCardToPlayed(Card *card);
    virtual Card* drawCard();

    CARD_COLOR last_played_color;
    CARD_VALUE last_played_value;
};

}}  // namespace

#endif  // SRC_UNO_GAME_DECK_H_
