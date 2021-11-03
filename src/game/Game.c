/*      Own include     */
#include "game/Game.h"

/*    System includes   */
#include <stdbool.h>
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "game/proxies/GameProxy.h"
#include "utils/drawing/Color.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

int32_t initGame(struct Game* self, const struct GameCfg* cfg) {
    if (SUCCESS != initGameLogic(&self->gameLogic)) {
        LOGERR("Error, initGameLogic() failed");
        return FAILURE;
    }

    if (SUCCESS != initGameBoard(&self->gameBoard, cfg->gameBoardRsrcId, 
            cfg->targetRsrcId, cfg->moveSelectorRsrcId)) {
        LOGERR("Error, initGameBoard() failed");
        return FAILURE;
    }

    if (SUCCESS != initPieceHandler(&self->pieceHandler, &cfg->pieceHandlerCfg, 
            self->gameLogic.activePlayerId, (void*)self, (void*)&self->gameBoard)) {
        LOGERR("Error, initChessPiece() failed");
        return FAILURE;
    }

    if (SUCCESS != initPiecePromotionPanel(&self->piecePromotionPanel, 
            &cfg->piecePromotionPanelCfg, (void*)self)) {
        LOGERR("Error, initPiecePromotionPanel() failed");
        return FAILURE;
    }

    return SUCCESS;
}

void deinitGame(struct Game* self) {
    deinitGameBoard(&self->gameBoard);
    deinitPieceHandler(&self->pieceHandler);
    deinitPiecePromotionPanel(&self->piecePromotionPanel);
}

void handleEventGame(struct Game* self, const struct InputEvent* event) {
    if (self->piecePromotionPanel.isActive) {
        handleEventPiecePromotionPanel(&self->piecePromotionPanel, event);
        return;
    }

    handleEventPieceHandler(&self->pieceHandler, event);
}

void drawGame(struct Game* self) {
    drawGameBoard(&self->gameBoard);
    drawPieceHandler(&self->pieceHandler);
    drawPiecePromotionPanel(&self->piecePromotionPanel);
}

/*Proxies*/
void finishTurnGameProxy(void* proxy) {
    struct Game* self = (struct Game*)proxy;
    finishTurn(&self->gameLogic);

    self->pieceHandler.currPlayerId = self->gameLogic.activePlayerId;
}

void activatePawnPromotionGameProxy(void* proxy) {
    struct Game* self = (struct Game*)proxy;
    LOGC("Piece prom active for playerId: %d", 
         self->gameLogic.activePlayerId);
    
    activatePiecePromotionPanel(&self->piecePromotionPanel, 
                                self->gameLogic.activePlayerId);
}

void onPiecePromotionSelectedGameProxy(void* proxy, PieceType pieceType) {
    struct Game* self = (struct Game*)proxy;
    promotePiecePieceHandler(&self->pieceHandler, pieceType);

    LOGC("Recieved piedeType: %d, %d", pieceType, self->pieceHandler.selectedPieceId);
}