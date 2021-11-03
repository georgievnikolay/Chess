/*      Own include     */
#include "game/entities/PiecePromotionPanel.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/proxies/PiecePromotionPanelProxy.h"
#include "game/config/PiecePromotionPanelCfg.h"
#include "game/config/PiecePromotionButtonCfg.h"
#include "game/proxies/GameProxy.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

int32_t initPiecePromotionPanel(struct PiecePromotionPanel *self,
                                const struct PiecePromotionPanelCfg *cfg,
                                void* gameProxy) {
    if (NULL == gameProxy) {
        LOGERR("Error, NULL provided for gameProxy");
        return FAILURE;
    }
    self->gameProxy = gameProxy;

    struct PiecePromotionButtonCfg buttonCfg;
    buttonCfg.panelProxy = (void*)self;

    buttonCfg.buttonBgrRsrcId = cfg->buttonBgrRsrcId;
    buttonCfg.buttonWhitePieceRsrcId = cfg->whitePiecesRsrcId;
    buttonCfg.buttonBlackPieceRsrcId = cfg->blackPiecesRsrcId;

    buttonCfg.bgrWidth = cfg->buttonBgrWidth;
    buttonCfg.bgrHeight = cfg->buttonBgrHeight;

    buttonCfg.width = cfg->buttonWidth;
    buttonCfg.height = cfg->buttonHeight;

    const PieceType pieceTypes[PROMOTE_BUTTONS_COUNT] = {
        QUEEN, ROOK, BISHOP, KNIGHT };
    
    const int32_t buttonXInitialOffsetPixels = 75;
    const int32_t buttonXOffsetPixels = 100;
    const int32_t startX = (cfg->gameBoardWidth - 
        PROMOTE_BUTTONS_COUNT * (cfg->buttonWidth + buttonXInitialOffsetPixels)) / 2;

    const int32_t startY = (cfg->gameBoardHeight - cfg->buttonHeight) / 2;
    buttonCfg.bgrPos.y = startY;
    
    for (int32_t i = 0; i < PROMOTE_BUTTONS_COUNT; i++) {
        buttonCfg.pieceType = pieceTypes[i]; 
        buttonCfg.bgrPos.x = startX + (i * (cfg->buttonWidth + buttonXOffsetPixels));

        if (SUCCESS != initPiecePromotionButton(&self->promotionBtns[i], &buttonCfg, self)) {
            LOGERR("initPiecePromotionButton() failed for relative id: %d", i);
            return FAILURE;
        }
    }

    self->isActive = false;
    return SUCCESS;
}

void deinitPiecePromotionPanel(struct PiecePromotionPanel *self) {
    for (int32_t i = 0; i < PROMOTE_BUTTONS_COUNT; i++) {
        deinitPiecePromotionButton(&self->promotionBtns[i]);
    }   
}

void handleEventPiecePromotionPanel(struct PiecePromotionPanel *self,
                                    const struct InputEvent *event) {
    for (int32_t i = 0; i < PROMOTE_BUTTONS_COUNT; i++) {
        if (self->promotionBtns[i].button.isInputUnlocked &&
            containsEventButton(&self->promotionBtns[i].button, event)) {
            
            handleEventPiecePromotionButton(&self->promotionBtns[i], event);
            break;
        }
    }
}

void drawPiecePromotionPanel(struct PiecePromotionPanel *self) {
    if (!self->isActive) {
        return;
    }

    for (int32_t i = 0; i < PROMOTE_BUTTONS_COUNT; i++) {
        drawPiecePiecePromotionButton(&self->promotionBtns[i]);
    }
}

void activatePiecePromotionPanel(struct PiecePromotionPanel *self, int32_t playerId) {
    self->isActive = true;

    for (int32_t i = 0; i < PROMOTE_BUTTONS_COUNT; i++) {
        activatePiecePromotionButton(&self->promotionBtns[i], playerId);
    }
}

/*Proxies*/
void onPieceTypeSelectedPromotionPanelProxy(void* proxy, PieceType pieceType) {
    struct PiecePromotionPanel* self = (struct PiecePromotionPanel*)proxy;
    self->isActive = false;

    onPiecePromotionSelectedGameProxy(self->gameProxy, pieceType);
}