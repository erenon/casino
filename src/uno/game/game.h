#ifndef UNO_GAME_GAME_H_
#define UNO_GAME_GAME_H_

#include "player_list.h"
#include "action_stack.h"
#include "../player/player.h"
#include "../action/card.h"
#include "../action/draw.h"

namespace Uno { namespace Game {

using ::Uno::Player::Player;
//CARD_COLOR/VALUE, Draw
using namespace ::Uno::Action;

class Game
{
protected:
	int max_player_count;

	PlayerList players;
	ActionStack deck;

	int current_penalty;
	Draw draw_action;

public:
	Game(int max_player_count);
	virtual ~Game() {};

	virtual void joinPlayer(Player *player);
	virtual int getPlayerCount();

	virtual void addCardToDeck(Card *card);

	virtual bool isPenalty();
	virtual void increasePenality(int addition);
	virtual void dealPenality(Player* player);
	virtual void dealCard(Player* player);

	virtual void blockNextPlayer();
	virtual void reverseTurn();
	virtual void drawCards();
	virtual Draw *getDrawAction();
	virtual void setLastColor(CARD_COLOR color);
};

}} //namespace

#endif /* UNO_GAME_GAME_H_ */
