/*      Own include     */
#include "game/entities/panels/GamePanels.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/config/GamePanelsCfg.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

int32_t initGamePanels(struct GamePanels* self, const struct GamePanelsCfg* cfg, void* proxy) {
    if (SUCCESS != initPiecePromotionPanel(&self->piecePromotionPanel, 
            &cfg->piecePromotionPanelCfg, proxy)) {
        LOGERR("Error, initPiecePromotionPanel() failed");
        return FAILURE;
    }

    if (SUCCESS != initGameStatePanel(&self->gameStatePanel, 
            &cfg->gameStatePanelCfg, proxy)) {
        LOGERR("Error, initGameStatePanel() failed");
        return FAILURE;
    }

    return SUCCESS;    
}

void deinitGamePanels(struct GamePanels* self) {
    deinitPiecePromotionPanel(&self->piecePromotionPanel);
    deinitGameStatePanel(&self->gameStatePanel);
}

void handleEventGameStatePanels(struct GamePanels* self, struct InputEvent* event) {
    handleEventGameStatePanel(&self->gameStatePanel, event);
    
    if (self->piecePromotionPanel.isActive) {
        handleEventPiecePromotionPanel(&self->piecePromotionPanel, event);
        return;
    }
}

void drawGamePanels(struct GamePanels* self) {
    drawPiecePromotionPanel(&self->piecePromotionPanel);
    drawGameStatePanel(&self->gameStatePanel);
}
