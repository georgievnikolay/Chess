/*      Own include     */
#include "game/Game.h"

/*    System includes   */
#include <stdbool.h>
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "game/proxies/GameInterface.h"
#include "sdl_utils/InputEvent.h"
#include "utils/drawing/Color.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

int32_t initGame(struct Game* self, const struct GameCfg* cfg) {
    if (SUCCESS != initHero(&self->hero, cfg->heroRsrcId)) {
        LOGERR("initHero() failed");
        return FAILURE;
    }

    if (SUCCESS != initWheel(&self->wheel, cfg->wheelRsrcId, cfg->rotWheelTimerId)) {
        LOGERR("initWheel() failed");
        return FAILURE;
    }

    const int32_t buttonIds[WHEEL_BUTTONS_COUNT] = { 
        cfg->startButtonRsrcId, 
        cfg->stopButtonRsrcId};

    const struct Point buttonPos[WHEEL_BUTTONS_COUNT] = {
        { .x = 680, .y = 100 }, { .x = 850, .y = 100 }
    };
    for (int32_t i = 0; i < WHEEL_BUTTONS_COUNT; i++) {
        if (initWheelButton(&self->wheelBtns[i], (void*)self, i, 
                            buttonIds[i], &buttonPos[i])) {
            LOGERR("initWheelButton() failed");
            return FAILURE;
        }
    }

    lockInputButton(&self->wheelBtns[STOP_BUTTON_ID].button);

    return SUCCESS;
}

void deinitGame(struct Game* self) {
    deinitHero(&self->hero);
    deinitWheel(&self->wheel);

    for (int32_t i = 0; i < WHEEL_BUTTONS_COUNT; i++) {
        deinitWheelButton(&self->wheelBtns[i]);
    }
}

void handleEventGame(struct Game* self, struct InputEvent* e) {
    handleEventHero(&self->hero, e);
    handleEventWheel(&self->wheel, e);

    for (int32_t i = 0; i < WHEEL_BUTTONS_COUNT; i++) {
        if (self->wheelBtns[i].button.isInputUnlocked && 
            containsEventButton(&self->wheelBtns[i].button, e)) {
            
            handleEventWheelButton(&self->wheelBtns[i], e);
            break;
        }
    }    
}

void drawGame(struct Game* self) {
    drawWheel(&self->wheel);
    drawHero(&self->hero);

    for (int32_t i = 0; i < WHEEL_BUTTONS_COUNT; i++) {
        drawWheelButton(&self->wheelBtns[i]);
    }
}

void onButtonPressedGameProxy(void* gameProxy, int32_t buttonId) {
    struct Game* game = (struct Game*)gameProxy;

    switch (buttonId) {
        case START_BUTTON_ID:
            lockInputButton(&game->wheelBtns[START_BUTTON_ID].button);
            unlockInputButton(&game->wheelBtns[STOP_BUTTON_ID].button);
            startAnimationWheel(&game->wheel);
            break;
        
        case STOP_BUTTON_ID:
            lockInputButton(&game->wheelBtns[STOP_BUTTON_ID].button);
            unlockInputButton(&game->wheelBtns[START_BUTTON_ID].button);
            stopAnimationWheel(&game->wheel);
            break;
        
        default:
            break;
    }
    
}
