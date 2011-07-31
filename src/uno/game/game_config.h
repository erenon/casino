#ifndef CSU_GAME_CONFIG_H_
#define CSU_GAME_CONFIG_H_

namespace Casino { namespace Uno { namespace Game {

struct GameConfig {
	int initial_hand_size;

	GameConfig()
		:initial_hand_size(7)
	{}
};

}}} //namespace

#endif /* CSU_GAME_CONFIG_H_ */
