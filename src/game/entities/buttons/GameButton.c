/*      Own include     */
#include "game/entities/buttons/GameButton.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */

/* Forward declarations */
#include "game/defines/GameDefines.h"
#include "game/config/GameButtonCfg.h"
#include "game/proxies/GameStatePanelProxy.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/*        Defines       */

int32_t initGameButton(struct GameButton* self, 
                       struct GameButtonCfg* cfg,
                       void* panelProxy,
                       int32_t buttonId) {
    if (panelProxy == NULL) {
        LOGERR("Error, NULL provided for gameButton proxy");
        return FAILURE;
    }        
    self->panelProxy = panelProxy;


    self->cfg = *cfg;
    self->buttonId = buttonId;
    resetButton(&self->base);
    createButton(&self->base, self->cfg.buttonRsrcId, &cfg->buttonPos);

    return SUCCESS;                
}

void deinitGameButton(struct GameButton* self) {
    destroyButton(&self->base);
}

void handleEventGameButton(struct GameButton* self, struct InputEvent* event) {
    if (event->type == TOUCH_PRESS) {
        setFrameImage(&self->base.img, CLICKED);
    } else if (event->type == TOUCH_RELEASE) {
        setFrameImage(&self->base.img, UNCLICKED);
        //comunicate with panel proxy
        //onButtonPressedGameProxy(self->proxy, self->buttonId);
        LOGY("BUTTON: %d", self->buttonId);
        switch (self->buttonId) {
            case START_GAME_BUTTON_ID:
                startGameGamePanelProxy(self->panelProxy);
                break;
            case EXIT_GAME_BUTTON_ID:
                exitGameGamePanelProxy(self->panelProxy);
                break;
            case QUIT_GAME_BUTTON_ID:
                quitGameGamePanelProxy(self->panelProxy);
                break;
            
            case CONTINUE_GAME_BUTTON_ID:
                continueGameGamePanelProxy(self->panelProxy);
                break;

            default:
                break;
        }
    }

}

void drawGameButton(struct GameButton* self) {
    drawButton(&self->base);
}