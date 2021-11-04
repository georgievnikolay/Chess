/*      Own include     */
#include "game/entities/pieces/types/ChessPiece.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "sdl_utils/InputEvent.h"
#include "game/utils/BoardUtils.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

int32_t initChessPiece(struct ChessPiece* self, const struct ChessPieceCfg* cfg) {
    if (!isInsideBoardBoardPos(&cfg->boardPos)) {
        LOGERR("Provided boardPos: [%d, %d] is outside of the boardPos for rsrcId: %d", 
            cfg->boardPos.row, cfg->boardPos.col, cfg->rsrcId);
        return FAILURE;
    }

    const struct Point absPos = getAbsPos(&cfg->boardPos);
    resetImage(&self->pieceImg);
    createImage(&self->pieceImg, cfg->rsrcId, &absPos);
    setFrameImage(&self->pieceImg, cfg->pieceType);
    
    self->boardPos = cfg->boardPos;
    self->playerId = cfg->playerId;
    self->pieceType = cfg->pieceType;
    
    return SUCCESS;
}

void deinitChessPiece(struct ChessPiece* self) {
    destroyImage(&self->pieceImg);
}

void drawChessPiece(struct ChessPiece* self) {
    drawImage(&self->pieceImg);
}

bool containsEventChessPiece(struct ChessPiece* self,
                             const struct InputEvent* event) {
    
    return containsPointWidget(&self->pieceImg.widget, &event->pos);
}

void setBoardPosChessPiece(struct ChessPiece* self,
                           const struct BoardPos* boardPos) {
    self->boardPos = *boardPos;
    const struct Point pos = getAbsPos(boardPos);
    setPositionWidget(&self->pieceImg.widget, &pos);
}