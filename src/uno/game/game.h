#ifndef CSU_GAME_H_
#define CSU_GAME_H_

#include "../../common/game/game.h"
#include "../player/player.h"
#include "../action/card.h"
#include <stack>
#include <vector>

namespace Casino { namespace Uno { namespace Game {

using ::Casino::Common::Game::Game;
using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Action::UnoCard;

class UnoGame :public Game
{
protected:
	int current_penality;

	class ActionStack {
	protected:
		std::stack<UnoCard *> deck;
		std::vector<UnoCard *> played;

		void shufflePlayedIntoDeck();
	public:
		void addCard(UnoCard *card);
		UnoCard* drawCard();
	} deck;

public:
	UnoGame(int max_player_count);
	void addCardToDeck(UnoCard *card);
	bool isPenality();
	void increasePenality(int addition);
	void dealPenality(UnoPlayer* player);
	void dealCard(UnoPlayer* player);

};

}}} //namespace

#endif /* CSU_GAME_H_ */
