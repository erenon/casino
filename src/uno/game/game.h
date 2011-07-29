#ifndef CSU_GAME_H_
#define CSU_GAME_H_

#include "../../common/game/game.h"
#include "../player/player.h"
#include "../action/card.h"
#include "../action/simple_card.h"
#include "../action/action.h"
#include "../action/draw.h"

#include <deque>
#include <list>
#include <string>

namespace Casino { namespace Uno { namespace Game {

using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Action::Action;
//CARD_COLOR/VALUE, Draw, Card, SimpleCard
using namespace ::Casino::Uno::Action;

class Game :public ::Casino::Common::Game::Game
{
protected:
	class PlayerList {
	protected:
		std::list<UnoPlayer *> players;
		bool turn_direction_normal;
		typedef std::list<UnoPlayer *>::iterator player_iterator;
		player_iterator current_player;
		UnoPlayer* prev_player;
		player_iterator determineNextPlayer();

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
		void notifyAll(Event::EVENT event_type, void* event);
		void notifyOthers(Event::EVENT event_type, void* event, UnoPlayer* player);
	} players;

	class ActionStack {
	protected:
		std::deque<Card *> deck;
		std::deque<Card *> played;

		static ptrdiff_t getrandom(ptrdiff_t i);
		void shuffle(std::deque<Card *> &toShuffle);
		void shufflePlayedIntoDeck();
	public:
		void shuffleDeck();
		void addCard(Card *card);
		void addCardToPlayed(Card *card);
		Card* drawCard();
		//Card *lastPlayedCard();
		CARD_COLOR last_played_color;
		CARD_VALUE last_played_value;
		virtual ~ActionStack() {};
	} deck;

	int current_penalty;
	Draw draw_action;

	UnoPlayer* previous_nonblocked_player;
	void checkUno();
	void registerNonblockedPlayer(UnoPlayer* player);

	void initStart();
	bool doesPlayerWin(UnoPlayer* player);


public:
	Game(int max_player_count);
	virtual void joinPlayer(UnoPlayer *player);
	void addCardToDeck(Card *card);
	bool isPenalty();
	void increasePenality(int addition);
	void dealPenality(UnoPlayer* player);
	void dealCard(UnoPlayer* player);

	void start();

	SimpleCard lastPlayedCard();
	bool isValidMove(Action* action, std::string &message);
	void blockNextPlayer();
	void reverseTurn();
	void drawCards();
	Draw *getDrawAction();
	void setLastColor(CARD_COLOR color);
};

}}} //namespace

#endif /* CSU_GAME_H_ */
