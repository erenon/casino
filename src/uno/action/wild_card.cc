#include "./wild_card.h"
#include "../game/game.h"

namespace Uno { namespace Action {

using ::Uno::Action::CARD_COLOR;
using ::Uno::Action::CARD_VALUE;

void WildCard::setColor(CARD_COLOR color) {
    choosen_color = color;
}

void WildCard::takeAction(Game* game) {
    game->setLastColor(choosen_color);
}

}}  // namespace
