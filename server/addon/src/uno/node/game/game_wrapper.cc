#include <nodejs/v8.h>
#include <nodejs/node.h>

#include "game_wrapper.h"
#include "../../game/async_game.h"

// TODO remove this include and std::cout prints
#include <iostream>

namespace Uno { namespace Node { namespace Game {

using namespace v8;
using namespace node;

using ::Uno::Game::AsyncGame;

void GameWrapper::Initialize(Handle<Object> target) {
    HandleScope scope;

    Local<FunctionTemplate> funcConstructorTemplate = FunctionTemplate::New(New);
    target->Set(String::NewSymbol("Game"), funcConstructorTemplate->GetFunction());

    v8::V8::AddGCEpilogueCallback(GcEpilogue);

    scope.Close(Undefined());
}

Handle<Value> GameWrapper::New(const Arguments &args) {
    HandleScope scope;

    // TODO add gameconfig here
    AsyncGame *game = new AsyncGame(4);

    Local<ObjectTemplate> instanceTemplate = ObjectTemplate::New();
    instanceTemplate->SetInternalFieldCount(1);

    Persistent<Object> instance = Persistent<Object>(instanceTemplate->NewInstance());
    instance->SetInternalField(0, External::New(game));
    V8::AdjustAmountOfExternalAllocatedMemory(sizeof(*game));

    instance.MakeWeak(game, CleanupGame);
    instance.MarkIndependent();

    Local<FunctionTemplate> start = FunctionTemplate::New(Start);
    Local<FunctionTemplate> joinPlayer = FunctionTemplate::New(JoinPlayer);
    Local<FunctionTemplate> getPlayerCount = FunctionTemplate::New(GetPlayerCount);
    Local<FunctionTemplate> dispose = FunctionTemplate::New(Dispose);

    instance->Set(
        String::New("start"),
        start->GetFunction()
    );

    instance->Set(
        String::New("joinPlayer"),
        joinPlayer->GetFunction()
    );

    instance->Set(
        String::New("getPlayerCount"),
        getPlayerCount->GetFunction()
    );

    instance->Set(
        String::New("dispose"),
        dispose->GetFunction()
    );

    return scope.Close(instance);
}

void GameWrapper::CleanupGame(Persistent<Value> object, void* parameter) {
    std::cout << "cleanup start" << std::endl;

    // TODO use UnwrapGame instead
    AsyncGame *game = static_cast<AsyncGame*>(parameter);
    delete game;

    object.Dispose();
    object.Clear();
}

AsyncGame* GameWrapper::UnwrapGame(Local<Object> Holder) {
    // TODO check for internal field count
    Local<External> gamePointer = Local<External>::Cast(Holder->GetInternalField(0));
    AsyncGame *game = static_cast<AsyncGame*>(gamePointer->Value());

    return game;
}

Handle<Value> GameWrapper::JoinPlayer(const v8::Arguments &args) {
    // TODO implement this
    HandleScope scope;

    return scope.Close(Undefined());
}

Handle<Value> GameWrapper::GetPlayerCount(const Arguments &args) {
    HandleScope scope;

    AsyncGame *game = UnwrapGame(args.Holder());
    return scope.Close(Number::New(game->getPlayerCount()));
}

Handle<Value> GameWrapper::Start(const Arguments &args) {
    HandleScope scope;

    AsyncGame *game = UnwrapGame(args.Holder());
    game->start();

    return scope.Close(Undefined());
}

Handle<Value> GameWrapper::Dispose(const v8::Arguments &args) {
    HandleScope scope;

    AsyncGame* game = UnwrapGame(args.Holder());
    delete game;

    return scope.Close(Undefined());
}

void GameWrapper::GcEpilogue(GCType type, GCCallbackFlags flags) {
    std::cout << "GC epilogue ============= " << std::endl;
}

}}}  // namespace
