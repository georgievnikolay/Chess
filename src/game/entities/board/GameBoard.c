/*      Own include     */
#include "game/entities/board/GameBoard.h"

/*    System includes   */
#include <stdlib.h>

/* Third party includes */

/* Own library includes */
#include "game/proxies/GameBoardProxy.h"
#include "game/defines/ChessStructs.h"
#include "game/utils/BoardUtils.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

static void clearMoveTiles(struct Vector* moveTiles) {
    const size_t size = getSizeVector(moveTiles);
    for (size_t i = 0; i < size; i++) {
        free(getElementVector(moveTiles, i));
    }

    freeVector(moveTiles);
}

int32_t initGameBoard(struct GameBoard* self, int32_t gameBoardRsrcId, 
                      int32_t targetRsrcId, int32_t moveSelectorRsrcId) {

    if (SUCCESS != initMoveSelector(&self->moveSelector, moveSelectorRsrcId)) {
        LOGERR("Error, initMoveSelector() failed");
        return FAILURE;
    }
    resetImage(&self->boardImg);
    createImage(&self->boardImg, gameBoardRsrcId, &POINT_ZERO);

    resetImage(&self->targetImg);
    createImage(&self->targetImg, targetRsrcId, &POINT_ZERO);
    hideWidget(&self->targetImg.widget);

    return SUCCESS;
}

void deinitGameBoard(struct GameBoard* self) {
    destroyImage(&self->boardImg);
    destroyImage(&self->targetImg);
    deinitMoveSelector(&self->moveSelector);
    clearMoveTiles(&self->currSelectedTiles);
}

void drawGameBoard(struct GameBoard* self) {
    drawImage(&self->boardImg);
    drawMoveSelector(&self->moveSelector);
    drawImage(&self->targetImg);
}


/*Proxies*/
void onPieceGrabbedGameBoardProxy(void* proxy, const struct BoardPos* boardPos,
                                  const struct Vector* moveTiles) {
    struct GameBoard* self = (struct GameBoard*)proxy;
    showWidget(&self->targetImg.widget);
    const struct Point absPos = getAbsPos(boardPos);
    setPositionWidget(&self->targetImg.widget, &absPos);

    markTilesMoveSelector(&self->moveSelector, moveTiles);
    shallowCopyVector(moveTiles, &self->currSelectedTiles);
}

void onPieceUngrabbedGameBoardProxy(void* proxy) {
    struct GameBoard* self = (struct GameBoard*)proxy;
    hideWidget(&self->targetImg.widget);

    unmarkTilesMoveSelector(&self->moveSelector);

    clearMoveTiles(&self->currSelectedTiles);
}

bool isMoveAllowedGameBoardProxy(void* proxy, const struct BoardPos* boardPos) {
    struct GameBoard* self = (struct GameBoard*)proxy;
    const struct TileData* tileData = NULL;

    const size_t size = getSizeVector(&self->currSelectedTiles);
    for (size_t i = 0; i < size; i++) {
        tileData = 
            (const struct TileData*)getElementVector(&self->currSelectedTiles, i);
        
        if (!areBoardPosEqual(boardPos, &tileData->boardPos)) {
            continue;
        }

        if (tileData->tileType == MOVE_TILE || tileData->tileType == TAKE_TILE) {
            return true;
        }
    }

    return false;
}