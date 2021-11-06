#ifndef INCLUDE_GAME_ENTITIES_BUTTONS_GAMEBUTTON_H_
#define INCLUDE_GAME_ENTITIES_BUTTONS_GAMEBUTTON_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "game/config/GameButtonCfg.h"
#include "manager_utils/input/Button.h"

/* Forward declarations */
struct InputEvent;

/*        Defines       */

struct GameButton {
    struct Button base;
    struct GameButtonCfg cfg;
    int32_t buttonId;
    void* panelProxy;
};

int32_t initGameButton(struct GameButton* self, 
                       struct GameButtonCfg* cfg,
                       void* panelProxy,
                       int32_t buttonId);

void deinitGameButton(struct GameButton* self);

void handleEventGameButton(struct GameButton* self, struct InputEvent* event);

void drawGameButton(struct GameButton* self);

#endif /* INCLUDE_GAME_ENTITIES_BUTTONS_GAMEBUTTON_H_ */