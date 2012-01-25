#ifndef SRC_UNO_ACTION_ACTION_H_
#define SRC_UNO_ACTION_ACTION_H_

namespace Uno { namespace Game {
    class Game;
}}  // namespace

namespace Uno { namespace Action {

using ::Uno::Game::Game;

class Action {

 public:
    virtual bool isDisposeable() = 0;
    virtual void takeAction(Game* game) = 0;
    virtual ~Action() {}
};

}}  // namespace

#endif  // SRC_UNO_ACTION_ACTION_H_