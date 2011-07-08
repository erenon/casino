#include "draw.h"

#include "../game/game.h"

namespace Casino { namespace Uno { namespace Action {

using ::Casino::Uno::Game::UnoGame;

bool Draw::isDisposeable() {
	return false;
}

void Draw::takeAction(UnoGame* game) {
	game->drawCards();
}

}}} //namespace
