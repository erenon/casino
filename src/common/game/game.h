#ifndef CSC_GAME_H_
#define CSC_GAME_H_

#include "../player/player.h"

namespace Casino { namespace Common { namespace Game {

using ::Casino::Common::Player::Player;

class Game
{
protected:
	int max_player_count;
	int player_count;
	Player** players;
public:
	Game(int max_player_count);
	virtual void joinPlayer(Player *player);
	virtual int getPlayerCount();
	virtual ~Game();
};

}}} //namespace

#endif /* CSC_GAME_H_ */
