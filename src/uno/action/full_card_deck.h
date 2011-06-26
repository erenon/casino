#ifndef CSU_FULL_CARD_DECK_H_
#define CSU_FULL_CARD_DECK_H_

#include "../game/game.h"
#include "card.h"
#include <list>

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Game::UnoGame;
using ::Casino::Uno::Action::UnoCard;

class UnoFullCardDeck
{
protected:
	std::list<UnoCard *> deck;
	UnoGame* game;
	void add(UnoCard *);
public:
	void fillGameWithCards(UnoGame* g);
	~UnoFullCardDeck();
};

}}} //namespace

#endif /* CSU_FULL_CARD_DECK_H_ */
