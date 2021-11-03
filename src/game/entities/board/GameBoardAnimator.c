/*      Own include     */
#include "game/entities/board/GameBoardAnimator.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/proxies/GameProxy.h"
#include "game/defines/ChessDefines.h"
#include "manager_utils/drawing/Image.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

int32_t initGameBoardAnimator(struct GameBoardAnimator* self,
                              void* gameProxy, 
                              struct Image* boardImg) {
    if (NULL == gameProxy) {
        LOGERR("Error, NULL provided for gameProxy");
        return FAILURE;
    }
    self->gameProxy = gameProxy;

    if (NULL == boardImg) {
        LOGERR("Error, NULL provided for boardImg");
        return FAILURE;
    }
    self->boardImg = boardImg;

    struct DrawParams* params = &self->boardImg->widget.drawParams;
    params->rotationCenter.x = params->frameRect.w / 2;
    params->rotationCenter.y = params->frameRect.h / 2;
    return SUCCESS;
}

void startAnimGameBoardAnimator(struct GameBoardAnimator* self, 
                                int32_t playerId) {
    if (WHITE_PLAYER_ID == playerId) {
        self->targetFlipType = HORIZONTAL_AND_VERTICAL_WIDGET_FLIP;
    } else {
        self->targetFlipType = NONE_WIDGET_FLIP;
    }
    setWidgetFlipTypeGameProxy(self->gameProxy, self->targetFlipType);
    
    onGameBoardAnimationFinishedGameProxy(self->gameProxy);
}