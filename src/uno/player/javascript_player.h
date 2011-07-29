#ifndef CSU_JAVASCRIPT_PLAYER_H_
#define CSU_JAVASCRIPT_PLAYER_H_

#include <node/v8.h>
#include <node/node.h>
#include <string>

#include "player.h"
#include "../action/action.h"
#include "../event/event.h"


namespace Casino { namespace Uno { namespace Game {
	class UnoGame;
}}} //namespace

namespace Casino { namespace Uno { namespace Player {

using namespace v8;
using ::Casino::Uno::Player::UnoPlayer;
using ::Casino::Uno::Action::Action;
using namespace ::Casino::Uno::Event;

class JavascriptUnoPlayer :public UnoPlayer
{
public:
	JavascriptUnoPlayer(Handle<Object> jsplayer);
	virtual Local<Function> getCallback(const char* cbname);
	virtual Action* pickAction(UnoGame *game);
	static Handle<Value> pickActionAfter(const Arguments &args);
	virtual Local<Object> createCardObject(UnoCard* card);
	virtual Local<Object> createPlayerObject(UnoPlayer* player);
	virtual void notify(EVENT event_type, void* event);

protected:
	std::string session_id;
	Persistent<Object> jsplayer;
};

}}} //namespace

#endif /* CSU_JAVASCRIPT_PLAYER_H_ */
