#include "plusfour_card.h"

#include "../game/game.h"

namespace Uno { namespace Action {

using ::Uno::Game::Game;

PlusfourCard::PlusfourCard() {
    color = CARD_COLOR_BLACK;
    value = CARD_VALUE_PLUSFOUR;
}

void PlusfourCard::takeAction(Game* game) {
    game->increasePenality(4);
    WildCard::takeAction(game);
}

}} //namespace
