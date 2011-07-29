#include "draw.h"

#include "../game/game.h"

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Game::Game;

bool Draw::isDisposeable() {
	return false;
}

void Draw::takeAction(Game* game) {
	game->drawCards();
}

}}} //namespace
