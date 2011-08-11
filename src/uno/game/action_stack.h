#ifndef UNO_GAME_ACTION_STACK_H_
#define UNO_GAME_ACTION_STACK_H_

#include "../action/card.h"

#include <deque>
//CARD_COLOR/VALUE, Card
using namespace ::Uno::Action;

namespace Uno { namespace Game {

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

}} //namespace

#endif /* UNO_GAME_ACTION_STACK_H_ */
