#ifndef UNO_ACTION_SIMPLE_CARD_H_
#define UNO_ACTION_SIMPLE_CARD_H_

#include "card.h"

namespace Uno { namespace Game {
    class Game;
}} //namespace

namespace Uno { namespace Action {

using ::Uno::Action::Card;
using ::Uno::Action::CARD_COLOR;
using ::Uno::Action::CARD_VALUE;

class SimpleCard :public Card
{
public:
    SimpleCard(CARD_COLOR color, CARD_VALUE value)
        :Card(color, value)
    {}

    virtual void takeAction(Game* game) {}
};

}} //namespace

#endif /* UNO_ACTION_SIMPLE_CARD_H_ */
