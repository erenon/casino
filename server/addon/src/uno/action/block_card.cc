#include "./block_card.h"

#include "../game/game.h"

namespace Uno { namespace Action {

using ::Uno::Game::Game;

BlockCard::BlockCard(CARD_COLOR color)
    :Card(color, CARD_VALUE_BLOCK)
{}

void BlockCard::takeAction(Game* game) {
    game->blockNextPlayer();
}

}}  // namespace
