/*      Own include     */
#include "game/Game.h"

/*    System includes   */
#include <stdbool.h>
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "utils/drawing/Color.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

int32_t initGame(struct Game* self, const struct GameCfg* cfg) {
    if (SUCCESS != initGameBoard(&self->gameBoard, cfg->gameBoardRsrcId, 
                                                   cfg->targetRsrcId)) {
        LOGERR("Error, initGameBoard() failed");
        return FAILURE;
    }

    if (SUCCESS != initPieceHandler(&self->pieceHandler, &cfg->pieceHandlerCfg, (void*)&self->gameBoard)) {
        LOGERR("Error, initChessPiece() failed");
        return FAILURE;
    }
    
    return SUCCESS;
}

void deinitGame(struct Game* self) {
    deinitGameBoard(&self->gameBoard);
    deinitPieceHandler(&self->pieceHandler);
}

void handleEventGame(struct Game* self, const struct InputEvent* event) {
    handleEventPieceHandler(&self->pieceHandler, event);
}

void drawGame(struct Game* self) {
    drawGameBoard(&self->gameBoard);
    drawPieceHandler(&self->pieceHandler);
}
