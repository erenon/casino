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
	std::list<UnoPlayer *> players;

	typedef std::list<UnoPlayer *>::iterator player_iterator;
	player_iterator current_player;
	bool turn_direction_normal;

	class ActionStack {
	protected:
		std::vector<UnoCard *> deck;
		std::vector<UnoCard *> played;

		void shuffle(std::vector<UnoCard *> toSuffle);
		void shufflePlayedIntoDeck();
	public:
		void shuffleDeck();
		void addCard(UnoCard *card);
		void addCardToPlayed(UnoCard *card);
		UnoCard* drawCard();
		UnoCard *lastPlayedCard();
		virtual ~ActionStack() {};
	} deck;

	void initStart();
	bool doesPlayerWin(UnoPlayer* player);
	player_iterator getPreviousPlayer();
	player_iterator getNextPlayer();
	void checkUno(UnoPlayer* player);

public:
	UnoGame(int max_player_count);
	virtual void joinPlayer(UnoPlayer *player);
	void addCardToDeck(UnoCard *card);
	bool isPenality();
	void increasePenality(int addition);
	void dealPenality(UnoPlayer* player);
	void dealCard(UnoPlayer* player);

	void start();

	UnoCard *lastPlayedCard();
	void blockNextPlayer();
	void reverseTurn();
};

}}} //namespace

#endif /* CSU_GAME_H_ */
