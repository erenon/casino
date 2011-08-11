#ifndef SRC_UNO_PLAYER_PLAYER_H_
#define SRC_UNO_PLAYER_PLAYER_H_

#include "../action/card.h"
#include "../event/event.h"
#include <vector>
#include <string>

namespace Uno { namespace Game {
    class Game;
}}  // namespace

namespace Uno { namespace Player {

using ::Uno::Action::Card;
namespace Event = ::Uno::Event;

class Player {

protected:
    std::string name;
    std::vector<Card*> hand;
    typedef std::vector<Card*>::iterator card_iterator;
    bool unoFlag;
    bool blocked;
public:
    Player();
    explicit Player(const char *name);
    virtual void setName(const char *name);
    virtual std::string getName();

    virtual void addCard(Card *card);
    virtual void removeCard(Card *card);

    virtual void notify(Event::EVENT event_type, void* event) = 0;
    virtual int getCardCount();
    virtual void setUnoFlag(bool value);
    virtual bool getUnoFlag();
    virtual bool isBlocked();
    virtual void block();
    virtual void unblock();
    virtual ~Player() {};
};

}}  // namespace


#endif  // SRC_UNO_PLAYER_PLAYER_H_
