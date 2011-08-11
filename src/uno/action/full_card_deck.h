#ifndef UNO_ACTION_FULL_CARD_DECK_H_
#define UNO_ACTION_FULL_CARD_DECK_H_

#include "../game/game.h"
#include "card.h"
#include <list>

namespace Uno { namespace Action {

using ::Uno::Game::Game;
using ::Uno::Action::Card;

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

}} //namespace

#endif /* UNO_ACTION_FULL_CARD_DECK_H_ */
