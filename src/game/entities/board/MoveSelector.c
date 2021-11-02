/*      Own include     */
#include "game/entities/board/MoveSelector.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessStructs.h"
#include "game/utils/BoardUtils.h"
#include "utils/containers/Vector.h"
#include "utils/ErrorCodes.h"

/* Forward declarations */

/*        Defines       */

int32_t initMoveSelector(struct MoveSelector* self, int32_t rsrcId) {
    for (int32_t i = 0; i < MAX_ACTIVE_TILES; i++) {
        resetImage(&self->tileImgs[i]);
        createImage(&self->tileImgs[i], rsrcId, &POINT_ZERO);
    }

    return SUCCESS;
}

void deinitMoveSelector(struct MoveSelector* self) {
    for (int32_t i = 0; i < MAX_ACTIVE_TILES; i++) {
        destroyImage(&self->tileImgs[i]);
    }
}

void drawMoveSelector(struct MoveSelector *self) {
    for (size_t i = 0; i < self->activeTiles; i++) {
        drawImage(&self->tileImgs[i]);
    }
}

void markTilesMoveSelector(struct MoveSelector *self,
                           const struct Vector *markedTiles) {
    const size_t size = getSizeVector(markedTiles);
    self->activeTiles = size;

    const struct TileData* tileData = NULL;
    for (size_t i = 0; i < size; i++) {
        tileData = (const struct TileData*)getElementVector(markedTiles, i);
        setFrameImage(&self->tileImgs[i], tileData->tileType);
        
        const struct Point pos = getAbsPos(&tileData->boardPos);
        setPositionWidget(&self->tileImgs[i].widget, &pos);
    }
}

void unmarkTilesMoveSelector(struct MoveSelector *self) {
    self->activeTiles = 0;
}