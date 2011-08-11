#ifndef UNO_GAME_ASYNC_GAME_H_
#define UNO_GAME_ASYNC_GAME_H_

#include "game.h"
#include "game_config.h"
#include "../player/player.h"
#include "../action/action.h"

namespace Uno { namespace Game {

using ::Uno::Player::Player;
using ::Uno::Action::Action;

class AsyncGame :public ::Uno::Game::Game
{
protected:
	GameConfig config;

public:
	AsyncGame(int max_player_count);
	void start();
	bool isValidMove(Player* player, Action* action, std::string &message);
	void takeAction(Player* player, Action* action);

	void drawCards();
};

}} //namespace

#endif /* UNO_GAME_ASYNC_GAME_H_ */
