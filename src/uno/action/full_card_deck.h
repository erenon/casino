#ifndef CSU_FULL_CARD_DECK_H_
#define CSU_FULL_CARD_DECK_H_

#include "../game/game.h"
#include "card.h"
#include <list>

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Game::Game;
using ::Casino::Uno::Action::Card;

class FullCardDeck
{
protected:
	std::list<Card *> deck;
	Game* game;
	void add(Card *);
public:
	void fillGameWithCards(Game* g);
	~FullCardDeck();
};

}}} //namespace

#endif /* CSU_FULL_CARD_DECK_H_ */
