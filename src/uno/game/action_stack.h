#ifndef CSU_ACTION_STACK_H_
#define CSU_ACTION_STACK_H_

#include "../action/card.h"

#include <deque>
//CARD_COLOR/VALUE, Card
using namespace ::Casino::Uno::Action;

namespace Casino { namespace Uno { namespace Game {

class ActionStack {
protected:
	std::deque<Card *> deck;
	std::deque<Card *> played;

	static ptrdiff_t getrandom(ptrdiff_t i);
	void shuffle(std::deque<Card *> &toShuffle);
	void shufflePlayedIntoDeck();
public:
	virtual ~ActionStack() {};
	void addCard(Card *card);
	void shuffleDeck();
	void playOutFirstCard();
	void addCardToPlayed(Card *card);
	Card* drawCard();

	CARD_COLOR last_played_color;
	CARD_VALUE last_played_value;
};

}}} //namespace

#endif /* CSU_ACTION_STACK_H_ */
