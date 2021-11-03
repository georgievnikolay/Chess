/*      Own include     */
#include "game/entities/buttons/PiecePromotionButton.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "game/proxies/PiecePromotionPanelProxy.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

int32_t initPiecePromotionButton(struct PiecePromotionButton *self,
                                const struct PiecePromotionButtonCfg *cfg,
                                void* panelProxy) {
    if (NULL == panelProxy) {
        LOGERR("Error, NULL provided for gameProxy");
        return FAILURE;
    }
    self->panelProxy = panelProxy;

    resetButton(&self->button);
    resetImage(&self->bgrImg);
    self->cfg = *cfg;

    createImage(&self->bgrImg, cfg->buttonBgrRsrcId, &cfg->bgrPos); 

    return SUCCESS;
}

void deinitPiecePromotionButton(struct PiecePromotionButton *self) {
    destroyImage(&self->bgrImg);
    if (self->button.img.widget.isCreated) {
        destroyButton(&self->button);
    }
}

void handleEventPiecePromotionButton(struct PiecePromotionButton *self,
                                    const struct InputEvent *event) {
    if (event->type == TOUCH_RELEASE) {
        onPieceTypeSelectedPromotionPanelProxy(self->panelProxy, self->cfg.pieceType);
    }
}

void drawPiecePiecePromotionButton(struct PiecePromotionButton *self) {
    drawImage(&self->bgrImg);
    drawButton(&self->button);
}

void activatePiecePromotionButton(struct PiecePromotionButton *self, 
                                  int32_t playerId) {
    const int32_t rsrcId = (playerId == WHITE_PLAYER_ID) ? 
                            self->cfg.buttonWhitePieceRsrcId : 
                            self->cfg.buttonBlackPieceRsrcId;

    if (self->button.img.widget.isCreated) {
        destroyButton(&self->button);
    }

    const struct DrawParams* params = &self->bgrImg.widget.drawParams;

    const int32_t X_Y_DELTA = (params->width - self->cfg.width) / 2;
    const struct Point btnPos = { .x = params->pos.x + X_Y_DELTA, 
                                  .y = params->pos.y + X_Y_DELTA };

    createButton(&self->button, rsrcId, &btnPos);
    setFrameImage(&self->button.img, self->cfg.pieceType);
}