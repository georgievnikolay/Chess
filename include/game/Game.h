#ifndef INCLUDE_GAME_GAME_H_
#define INCLUDE_GAME_GAME_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "game/config/GameCfg.h"
#include "game/entities/Hero.h"
#include "game/entities/Wheel.h"
#include "game/entities/buttons/WheelButton.h"
#include "manager_utils/drawing/Text.h"
#include "utils/drawing/DrawParams.h"

/* Forward declarations */
struct InputEvent;

/*        Defines       */

enum WheelButtons {
    START_BUTTON_ID,
    STOP_BUTTON_ID,
    WHEEL_BUTTONS_COUNT
};

struct Game {
    struct Hero hero;
    struct Wheel wheel;
    struct WheelButton wheelBtns[WHEEL_BUTTONS_COUNT];
};

int32_t initGame(struct Game* self, const struct GameCfg* cfg);

void deinitGame(struct Game* self);

void handleEventGame(struct Game* self, struct InputEvent* e);

void drawGame(struct Game* self);

#endif /* INCLUDE_GAME_GAME_H_ */