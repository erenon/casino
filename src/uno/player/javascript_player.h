#ifndef CSU_JAVASCRIPT_PLAYER_H_
#define CSU_JAVASCRIPT_PLAYER_H_

#include <node/v8.h>
#include <node/node.h>
#include <string>

#include "player.h"
#include "../action/action.h"
#include "../event/event.h"


namespace Casino { namespace Uno { namespace Game {
	class AsyncGame;
	class ConsoleGame;
}}} //namespace

namespace Casino { namespace Uno { namespace Player {

using namespace v8;
using ::Casino::Uno::Player::Player;
using ::Casino::Uno::Action::Action;
using ::Casino::Uno::Game::AsyncGame;
using ::Casino::Uno::Game::ConsoleGame;
using namespace ::Casino::Uno::Event;

class JavascriptPlayer :public Player
{
public:
	JavascriptPlayer(Handle<Object> jsplayer);
	virtual void setGame(AsyncGame* game);
	virtual Local<Function> getCallback(const char* cbname);
	virtual void addAction(Action *action);
	Handle<Value> playCard(const Arguments &args);
	virtual Action* pickAction(ConsoleGame *game);
	virtual Action* pickAction(AsyncGame *game);
	virtual Local<Object> createCardObject(Card* card);
	virtual Local<Object> createPlayerObject(Player* player);
	virtual void notify(EVENT event_type, void* event);

protected:
	std::string session_id;
	Persistent<Object> jsplayer;
	AsyncGame* game;

	void setJavascriptCallbacks();

private:
	JavascriptPlayer(JavascriptPlayer &player) {}
};

}}} //namespace

#endif /* CSU_JAVASCRIPT_PLAYER_H_ */
