/*      Own include     */
#include "game/entities/pieces/types/UnfinishedPiece.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/utils/BoardUtils.h"
#include "utils/drawing/Color.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

int32_t initUnfinishedPiece(struct UnfinishedPiece* self, 
                            const struct ChessPieceCfg* cfg, int32_t fontId) {
    if (initChessPiece(&self->base, cfg)) {
        LOGERR("Error, initChessPiece() dailed for rsrcId: %d", cfg->rsrcId);
        return FAILURE;
    }
    self->base.isUnfinished = true;

    resetText(&self->notReadyText);
    const struct Point textPos = getAbsPos(&self->base.boardPos);
    createText(&self->notReadyText, "!", fontId, &COLOR_RED, &textPos);
    return SUCCESS;
}

void deinitUnfinishedPiece(struct UnfinishedPiece* self) {
    destroyText(&self->notReadyText);
    deinitChessPiece(&self->base);
}

void drawUnfinishedPiece(struct UnfinishedPiece* self) {
    drawChessPiece(&self->base);
    drawText(&self->notReadyText);
}

void setBoardPosUnfinishedPiece(struct UnfinishedPiece* self,
                                const struct BoardPos* boardPos) {
    setBoardPosChessPiece(&self->base, boardPos);
    const struct Point textPos = getAbsPos(&self->base.boardPos);
    setPositionWidget(&self->notReadyText.widget, &textPos);
}

struct Vector getMoveTilesUnfinishedPiece(
    struct UnfinishedPiece* self, const struct Vector pieces[PLAYERS_COUNT]) {
    UNUSED(self);
    UNUSED(pieces);
    struct Vector emptyVec;
    initVector(&emptyVec, 0);
    return emptyVec;
}