/*      Own include     */
#include "game/utils/BoardUtils.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/utils/BoardPos.h"
#include "utils/drawing/Point.h"
#include "utils/drawing/Rectangle.h"

/* Forward declarations */

/*        Defines       */

static const int32_t BOARD_SIZE = 8;

static const int32_t FIRST_TILE_X_POS = 0;
static const int32_t FIRST_TILE_Y_POS = 0;

static const int32_t TILE_SIZE = 100;

struct BoardPos getBoardPos(const struct Point *absPos) {
    const struct BoardPos boardPos = { 
        .row = (absPos->y - FIRST_TILE_Y_POS) / TILE_SIZE,
        .col = (absPos->x - FIRST_TILE_X_POS) / TILE_SIZE };

    return boardPos;
}

struct Point getAbsPos(const struct BoardPos *boardPos) {
    const struct Point point = { 
        .x = (boardPos->col * TILE_SIZE) + FIRST_TILE_X_POS,
        .y = (boardPos->row * TILE_SIZE) + FIRST_TILE_Y_POS};
        
    return point;
}

bool isInsideBoardBoardPos(const struct BoardPos *boardPos) {
    if (0 > boardPos->col || 0 > boardPos->row) {
        return false;
    }

    if (boardPos->col >= BOARD_SIZE || boardPos->row >= BOARD_SIZE) {
        return false;
    }

    return true;
}

bool isInsideBoardPoint(const struct Point *absPos) {
    const int32_t BOARD_WIDTH_HEIGHT = BOARD_SIZE * TILE_SIZE;
    const struct Rectangle boardRect = 
        { .x = FIRST_TILE_X_POS,   .y = FIRST_TILE_Y_POS,
          .w = BOARD_WIDTH_HEIGHT, .h = BOARD_WIDTH_HEIGHT };

    return isPointInsideRect(absPos, &boardRect);
}