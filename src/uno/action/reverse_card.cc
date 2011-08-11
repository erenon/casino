#include "reverse_card.h"

#include "../game/game.h"

namespace Uno { namespace Action {

using ::Uno::Game::Game;

ReverseCard::ReverseCard(CARD_COLOR color)
    :Card(color, CARD_VALUE_REVERSE)
{}

void ReverseCard::takeAction(Game* game) {
    game->reverseTurn();
}

}} //namespace
