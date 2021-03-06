#ifndef INCLUDE_GAME_LOGIC_GAMELOGIC_H_
#define INCLUDE_GAME_LOGIC_GAMELOGIC_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "common/TimerDefines.h"
#include "game/defines/GameLogicDefines.h"
#include "manager_utils/time/TimerClient.h"
#include "manager_utils/drawing/Text.h"

/* Forward declarations */
struct GameLogicCfg;

/*        Defines       */

struct GameLogic {
    struct TimerClient timerClent;
    struct Text gameLogicTexts[TEXTS_COUNT];

    void* gameProxy;
    
    int32_t turnSeconds;
    int32_t activePlayerId;
    int32_t numberOfMoves;
};

int32_t initGameLogic(struct GameLogic* self, 
                      const struct GameLogicCfg* cfg, 
                      void* gameProxy);

void deinitGameLogic(struct GameLogic* self);

void drawGameLogic(struct GameLogic* self);

void finishTurn(struct GameLogic* self);

void startGameLogic(struct GameLogic* self);

void stopGameLogic(struct GameLogic* self);

int32_t loadGameLogic(struct GameLogic* gameLogic, const char* fileName);

int32_t saveGameLogic(const struct GameLogic* gameLogic);

#endif /* INCLUDE_GAME_LOGIC_GAMELOGIC_H_ */