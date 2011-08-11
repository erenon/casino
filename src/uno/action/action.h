#ifndef UNO_ACTION_ACTION_H_
#define UNO_ACTION_ACTION_H_

namespace Uno { namespace Game {
    class Game;
}} //namespace

namespace Uno { namespace Action {

using ::Uno::Game::Game;

class Action
{
public:
    virtual bool isDisposeable() = 0;
    virtual void takeAction(Game* game) = 0;
};

}} //namespace

#endif /* UNO_ACTION_ACTION_H_ */
