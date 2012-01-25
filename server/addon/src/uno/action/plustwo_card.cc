#include "./plustwo_card.h"

#include "../game/game.h"

namespace Uno { namespace Action {

using ::Uno::Game::Game;

PlustwoCard::PlustwoCard(CARD_COLOR color)
    :Card(color, CARD_VALUE_PLUSTWO)
{}

void PlustwoCard::takeAction(Game* game) {
    game->increasePenality(2);
}

}}  // namespace
