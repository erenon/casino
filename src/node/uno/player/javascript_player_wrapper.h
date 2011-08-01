#ifndef CSNU_JAVASCRIPT_PLAYER_WRAPPER_H_
#define CSNU_JAVASCRIPT_PLAYER_WRAPPER_H_

#include <node/v8.h>
#include <node/node.h>

#include "../../../uno/player/javascript_player.h"

namespace Casino { namespace Node { namespace Uno { namespace Player {

using namespace v8;
using namespace node;
using ::Casino::Uno::Player::JavascriptPlayer;

class JavascriptPlayerWrapper
:public ObjectWrap
{
public:
	static void Initialize(Handle<Object> target);
	static Handle<Value> New(const Arguments &args);
	static Handle<Value> PlayCard(const Arguments &args);
	static Handle<Value> Dispose(const Arguments &args);

	JavascriptPlayer* getNativePlayer();
	~JavascriptPlayerWrapper();

protected:
	JavascriptPlayer* player;

	JavascriptPlayerWrapper(Handle<Object> jsplayer);
};

}}}} //namespace

#endif /* CSNU_JAVASCRIPT_PLAYER_WRAPPER_H_ */
