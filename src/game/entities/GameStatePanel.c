/*      Own include     */
#include "game/entities/GameStatePanel.h"

/*    System includes   */
#include <stdlib.h>

/* Third party includes */

/* Own library includes */

/* Forward declarations */
#include "game/config/GameStatePanelCfg.h"
#include "game/proxies/GameProxy.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/*        Defines       */

int32_t initGameStatePanel(struct GameStatePanel* self,
                           const struct GameStatePanelCfg* cfg,
                           void* gameProxy) {
    if (NULL == gameProxy) {
        LOGERR("Error, NULL provided for gameProxy");
        return FAILURE;
    }
    self->gameProxy = gameProxy;

    struct GameButtonCfg buttonCfg;
    // buttonCfg.panelProxy = (void*)self;

    buttonCfg.buttonWidth = cfg->buttonWidth;
    buttonCfg.buttonHeight = cfg->buttonHeight;

    const int32_t buttonsRsrcIds[GAME_BUTTONS_COUNT] = {
        cfg->startButtonRsrcId, cfg->continueButtonRsrcId,
        cfg->exitButtonRsrcId, cfg->quitButtonRsrcId};

    const int32_t buttonYOffsetPixels = 50;  
    const int32_t startX = cfg->gameScreenWidth - 1.5*cfg->buttonWidth;
    const int32_t startY = cfg->buttonHeight;

    buttonCfg.buttonPos.x = startX;
    for (int32_t i = 0; i < GAME_BUTTONS_COUNT; i++) {
        buttonCfg.buttonRsrcId = buttonsRsrcIds[i];
        buttonCfg.buttonPos.y = startY + (i * (cfg->buttonHeight + buttonYOffsetPixels));

        /* Quit Game Button Position */
        if (buttonsRsrcIds[i] == cfg->quitButtonRsrcId) {
            buttonCfg.buttonPos.x = cfg->gameBoardWidth_Height + 
                (((cfg->gameScreenWidth - cfg->gameBoardWidth_Height) - cfg->buttonWidth) / 2);
            buttonCfg.buttonPos.y = cfg->buttonHeight;
        }

        if (SUCCESS != initGameButton(&self->gameButtons[i], &buttonCfg, self, i)) {
            LOGERR("initGameButton() failed for relative id: %d", i);
            return FAILURE;
        }
    }
    resetImage(&self->panelImg);
    createImage(&self->panelImg, cfg->startScreenRsrcId, &POINT_ZERO);
    self->isActive = true;
    return SUCCESS;
}

void deinitGameStatePanel(struct GameStatePanel* self) {
    destroyImage(&self->panelImg);
    for (int32_t i = 0; i < GAME_BUTTONS_COUNT; i++) {
        deinitGameButton(&self->gameButtons[i]);
    }
}

void handleEventGameStatePanel(struct GameStatePanel* self,
                               struct InputEvent* event) {
    for (int32_t i = 0; i < GAME_BUTTONS_COUNT; i++) {
        if (self->gameButtons[i].base.isInputUnlocked &&
            containsEventButton(&self->gameButtons[i].base, event)) {
            
            handleEventGameButton(&self->gameButtons[i], event);
            break;
        }
    }    
}

void drawGameStatePanel(struct GameStatePanel* self) {
    if (!self->isActive) {
        drawGameButton(&self->gameButtons[QUIT_GAME_BUTTON_ID]);
    } else {
        drawImage(&self->panelImg);
        for (int32_t i = 0; i < GAME_BUTTONS_COUNT - 1; i++) {
            drawGameButton(&self->gameButtons[i]);
        }
    }
}

void activateGameStatePanel(struct GameStatePanel* self) {
    self->isActive = true;

    for (int32_t i = 0; i < GAME_BUTTONS_COUNT; i++) {
        self->gameButtons[i].base.img.widget.isVisible = true;
    }
}

/* Proxies */
void startGameGamePanelProxy(void* proxy) {
    struct GameStatePanel* self = (struct GameStatePanel*)proxy;
    self->isActive = false;

    self->gameButtons[START_GAME_BUTTON_ID].base.isInputUnlocked = false;
    self->gameButtons[CONTINUE_GAME_BUTTON_ID].base.isInputUnlocked = false;
    self->gameButtons[EXIT_GAME_BUTTON_ID].base.isInputUnlocked = false;

    //TODO: add check
    onGameStartedGameProxy(self->gameProxy);
}

void exitGameGamePanelProxy(void* proxy) {
    /* Proxy to the game to tell it to exit */
    struct GameStatePanel* self = (struct GameStatePanel*)proxy;

    
    /* TODO: That pretty much sums up my knowledge */
    onGameExitedGameProxy(&self->gameProxy);
    exit(0);
}

void quitGameGamePanelProxy(void* proxy) {
    struct GameStatePanel* self = (struct GameStatePanel*)proxy;
    self->isActive = true;

    self->gameButtons[START_GAME_BUTTON_ID].base.isInputUnlocked = true;
    self->gameButtons[CONTINUE_GAME_BUTTON_ID].base.isInputUnlocked = true;
    self->gameButtons[EXIT_GAME_BUTTON_ID].base.isInputUnlocked = true;
    
    //TODO: add check
    onGameSavedGameProxy(self->gameProxy);
}

void continueGameGamePanelProxy(void* proxy) {
    struct GameStatePanel* self = (struct GameStatePanel*)proxy;
    self->isActive = false; 

    self->gameButtons[START_GAME_BUTTON_ID].base.isInputUnlocked = false;
    self->gameButtons[CONTINUE_GAME_BUTTON_ID].base.isInputUnlocked = false;
    self->gameButtons[EXIT_GAME_BUTTON_ID].base.isInputUnlocked = false;    

     //TODO: add check
    onGameContinueGameProxy(self->gameProxy);
}