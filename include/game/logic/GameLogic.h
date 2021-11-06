#ifndef INCLUDE_GAME_LOGIC_GAMELOGIC_H_
#define INCLUDE_GAME_LOGIC_GAMELOGIC_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */

/* Forward declarations */

/*        Defines       */

struct GameLogic {
    int32_t activePlayerId;
};

int32_t initGameLogic(struct GameLogic* self);

void finishTurn(struct GameLogic* self);

int32_t loadGameLogic(struct GameLogic* gameLogic, char* fileName);

int32_t saveGameLogic(const struct GameLogic* gameLogic);

#endif /* INCLUDE_GAME_LOGIC_GAMELOGIC_H_ */