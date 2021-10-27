/*      Own include     */
#include "game/entities/board/GameBoard.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "utils/ErrorCodes.h"
#include "game/utils/BoardUtils.h"
/* Forward declarations */

/*        Defines       */

int32_t initGameBoard(struct GameBoard* self, int32_t gameBoardRsrcId, 
                                              int32_t targetRsrcId) {
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
}

void drawGameBoard(struct GameBoard* self) {
    drawImage(&self->boardImg);
    drawImage(&self->targetImg);
}

void onPieceGrabbed(void* proxy, const struct BoardPos* boardPos) {
    struct GameBoard* self = (struct GameBoard*)proxy;
    showWidget(&self->targetImg.widget);
    const struct Point absPos = getAbsPos(boardPos);
    setPositionWidget(&self->targetImg.widget, &absPos);
}

void onPieceUngrabbed(void* proxy) {
    struct GameBoard* self = (struct GameBoard*)proxy;
    hideWidget(&self->targetImg.widget);    
}