#ifndef CSU_GAME_H_
#define CSU_GAME_H_

#include "../../common/game/game.h"
#include "../player/player.h"
#include "../action/card.h"
#include <deque>
#include <list>

namespace Casino { namespace Uno { namespace Game {

using ::Casino::Common::Game::Game;
using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Action::UnoCard;

class UnoGame :public Game
{
protected:
	int current_penality;

	class PlayerList {
	protected:
		std::list<UnoPlayer *> players;
		bool turn_direction_normal;
		typedef std::list<UnoPlayer *>::iterator player_iterator;
		player_iterator current_player;

	public:
		PlayerList();
		void joinPlayer(UnoPlayer *player);
		int size();
		UnoPlayer *getNextPlayer();
		UnoPlayer *getPreviousPlayer();
		UnoPlayer *getCurrentPlayer();
		UnoPlayer *next();
		void reset();
		void reverseTurn();
	} players;

	class ActionStack {
	protected:
		std::deque<UnoCard *> deck;
		std::deque<UnoCard *> played;

		void shuffle(std::deque<UnoCard *> toSuffle);
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
