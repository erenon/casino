#ifndef CSU_PLAYER_LIST_H_
#define CSU_PLAYER_LIST_H_

#include "../player/player.h"

#include <list>

namespace Casino { namespace Uno { namespace Game {

using ::Casino::Uno::Player::Player;

class PlayerList {
protected:
	std::list<Player *> players;
	bool turn_direction_normal;
	typedef std::list<Player *>::iterator player_iterator;
	player_iterator current_player;
	Player* prev_player;
	player_iterator determineNextPlayer();

public:
	PlayerList();
	void joinPlayer(Player *player);
	int size();
	Player *getNextPlayer();
	Player *getPreviousPlayer();
	Player *getCurrentPlayer();
	Player *next();
	void reset();
	void reverseTurn();
	void notifyAll(Event::EVENT event_type, void* event);
	void notifyOthers(Event::EVENT event_type, void* event, Player* player);
};

}}} //namespace

#endif /* CSU_PLAYER_LIST_H_ */