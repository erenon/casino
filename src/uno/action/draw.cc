#include "draw.h"

#include "../game/game.h"

namespace Uno { namespace Action {

using ::Uno::Game::Game;

bool Draw::isDisposeable() {
	return false;
}

void Draw::takeAction(Game* game) {
	game->drawCards();
}

}} //namespace
