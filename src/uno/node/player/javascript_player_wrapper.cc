#include "javascript_player_wrapper.h"

#include <string>
#include <stdexcept>

namespace Uno { namespace Node { namespace Player {

#define REQ_OBJ_ARG(I)                                                  \
    if (args.Length() <= (I) || !args[I]->IsObject()) {                 \
        return ThrowException(Exception::TypeError(                     \
            String::New("Argument " #I " must be an object")));         \
    }

JavascriptPlayerWrapper::JavascriptPlayerWrapper(Handle<Object> jsplayer) {
	player = new AsyncPlayer(jsplayer);
}

void JavascriptPlayerWrapper::Initialize(Handle<Object> target) {
	HandleScope scope;

	// t is a container
	Local<FunctionTemplate> t = FunctionTemplate::New(New);
	t->InstanceTemplate()->SetInternalFieldCount(1);

	NODE_SET_PROTOTYPE_METHOD(t, "playCard", PlayCard);
	NODE_SET_PROTOTYPE_METHOD(t, "draw", Draw);
	NODE_SET_PROTOTYPE_METHOD(t, "dispose", Dispose);

	target->Set(String::NewSymbol("Player"), t->GetFunction());
}

Handle<Value> JavascriptPlayerWrapper::New(const Arguments &args) {
	HandleScope scope;

	REQ_OBJ_ARG(0);

	JavascriptPlayerWrapper* wrapper = new JavascriptPlayerWrapper(args[0]->ToObject());
	wrapper->Wrap(args.This());

	return args.This();
}

Handle<Value> JavascriptPlayerWrapper::PlayCard(const Arguments &args) {
	HandleScope scope;

	JavascriptPlayerWrapper* wrapper = ObjectWrap::Unwrap<JavascriptPlayerWrapper>(args.This());

	try {
		wrapper->player->playCard(args);
	} catch (std::invalid_argument &e) {
		return ThrowException(Exception::TypeError(
            String::New(e.what())
		));
	} catch (std::domain_error &e) {
		return ThrowException(Exception::Error(
            String::New(e.what())
		));
	}

	return scope.Close(Undefined());
}

Handle<Value> JavascriptPlayerWrapper::Draw(const Arguments &args) {
	HandleScope scope;

	JavascriptPlayerWrapper* wrapper = ObjectWrap::Unwrap<JavascriptPlayerWrapper>(args.This());

	try {
		wrapper->player->draw();
	} catch (std::invalid_argument &e) {
		return ThrowException(Exception::TypeError(
            String::New(e.what())
		));
	} catch (std::domain_error &e) {
		return ThrowException(Exception::Error(
            String::New(e.what())
		));
	}

	return scope.Close(Undefined());
}

Handle<Value> JavascriptPlayerWrapper::Dispose(const Arguments &args) {
	HandleScope scope;
	JavascriptPlayerWrapper* wrapper = ObjectWrap::Unwrap<JavascriptPlayerWrapper>(args.This());

	delete wrapper->player;

	return scope.Close(Undefined());
}

AsyncPlayer* JavascriptPlayerWrapper::getNativePlayer() {
	return player;
}

JavascriptPlayerWrapper::~JavascriptPlayerWrapper() {
	delete player;
}

#undef REQ_OBJ_ARG

}}} //namespace
