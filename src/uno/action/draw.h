#ifndef UNO_ACTION_DRAW_H_
#define UNO_ACTION_DRAW_H_

#include "../action/action.h"

namespace Uno { namespace Game {
    class Game;
}} //namespace

namespace Uno { namespace Action {

using ::Uno::Action::Action;
using ::Uno::Game::Game;

class Draw :public Action
{
public:
    bool isDisposeable();
    void takeAction(Game* game);
};

}} //namespace

#endif /* UNO_ACTION_DRAW_H_ */
