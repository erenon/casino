#ifndef SRC_UNO_GAME_GAME_CONFIG_H_
#define SRC_UNO_GAME_GAME_CONFIG_H_

namespace Uno { namespace Game {

struct GameConfig {
    int initial_hand_size;

    GameConfig()
        :initial_hand_size(7)
    {}
};

}} //namespace

#endif  // SRC_UNO_GAME_GAME_CONFIG_H_
