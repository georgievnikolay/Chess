/*      Own include     */
#include "game/utils/BoardUtils.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/utils/BoardPos.h"
#include "game/entities/pieces/types/ChessPiece.h"
#include "utils/containers/Vector.h"
#include "utils/drawing/Point.h"
#include "utils/drawing/Rectangle.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

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

int32_t getOpponentId(int32_t activePlayerId) {
    if (activePlayerId == WHITE_PLAYER_ID) {
        return BLACK_PLAYER_ID;
    }

    return WHITE_PLAYER_ID;
}

struct BoardPos getAdjacentPos(Direction dir, const struct BoardPos *currPos) {
    struct BoardPos pos = *currPos;

    switch (dir) {
        case UP:
            --pos.row;
            break;

        case UP_LEFT:
            --pos.col;
            --pos.row;
            break;

        case LEFT:
            --pos.col;
            break;

        case DOWN_LEFT:
            --pos.col;
            ++pos.row;        
            break;

        case DOWN:
            ++pos.row;            
            break;

        case DOWN_RIGHT:
            ++pos.col;
            ++pos.row;
            break;

        case RIGHT:
            ++pos.col;
            break;

        case UP_RIGHT:
            ++pos.col;
            --pos.row;
            break;

        case KNIGHT_UP_LEFT_LOWER:
            pos.row -= 1;
            pos.col -= 2;
            break;

        case KNIGHT_UP_LEFT_UPPER:
            pos.row -= 2;
            pos.col -= 1;
            break;

        case KNIGHT_UP_RIGHT_LOWER:
            pos.row -= 1;
            pos.col += 2;
            break;

        case KNIGHT_UP_RIGHT_UPPER:
            pos.row -= 2;
            pos.col += 1;
            break;

        case KNIGHT_DOWN_RIGHT_LOWER:
            pos.row += 2;
            pos.col += 1;
            break;

        case KNIGHT_DOWN_RIGHT_UPPER:
            pos.row += 1;
            pos.col += 2;
            break;

        case KNIGHT_DOWN_LEFT_LOWER:
            pos.row += 2;
            pos.col -= 1;
            break;

        case KNIGHT_DOWN_LEFT_UPPER:
            pos.row += 1;
            pos.col -= 2;
            break;
                        
        default:
            LOGERR("Error, recieved unsupported direction: %d", dir);
            break;
    }

    return pos;
}

bool doCollideWithPiece(const struct BoardPos *selectedPos,
                        const struct Vector *pieces,
                        int32_t *outCollisionRelativeId) {
    
    const struct ChessPiece* piece = NULL;
    const size_t size = getSizeVector(pieces);
    for (size_t i = 0; i < size; i++) {
        piece = (const struct ChessPiece*)getElementVector(pieces, i);

        if (areBoardPosEqual(selectedPos, &piece->boardPos)) {
            *outCollisionRelativeId = (int32_t)i;
            return true;
        }
    }

    *outCollisionRelativeId = -1;
    return false;
}

TileType getTileType(const struct BoardPos *boardPos,
                                  const struct Vector *playerPieces,
                                  const struct Vector *enemyPieces) {
    int32_t foundIdx = 0;

    if (doCollideWithPiece(boardPos, playerPieces, &foundIdx)) {
        return GUARD_TILE;
    }

    if (doCollideWithPiece(boardPos, enemyPieces, &foundIdx)) {
        return TAKE_TILE;
    }

    return MOVE_TILE;
}