/*      Own include     */
#include "game/entities/pieces/types/King.h"

/*    System includes   */
#include <stdlib.h>

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessStructs.h"
#include "game/entities/pieces/types/ChessPiece.h"
#include "game/utils/BoardUtils.h"
#include "game/utils/BoardMoveHelper.h"

/* Forward declarations */

/*        Defines       */

enum KingDefines {
    KING_ALLOWED_DIRS = 8,
    KING_MAX_MOVES = 8
};

static void getBoardMoves(const struct ChessPiece* piece,
                          struct BoardMoveHelper* moveHelper) {
    struct BoardPos* pos = NULL;
    struct BoardPos futurePos;

    const Direction dirs[KING_ALLOWED_DIRS] = { 
        UP, UP_RIGHT, RIGHT, DOWN_RIGHT,
        DOWN, DOWN_LEFT, LEFT, UP_LEFT};

    for (int32_t i = 0; i < KING_ALLOWED_DIRS; i++) {
        const Direction currDir = dirs[i];
        futurePos = getAdjacentPos(currDir, &piece->boardPos);
        
        if (!isInsideBoardBoardPos(&futurePos)) {
            continue;
        }

        moveHelper->isDirUsed[currDir] = true;
        pos = (struct BoardPos*)malloc(sizeof(struct BoardPos));
        *pos = futurePos;

        pushElementVector(&moveHelper->moveDirs[currDir], pos);
    }
}

struct Vector getMoveTilesKing(const struct ChessPiece* self, 
                               const struct Vector pieces[PLAYERS_COUNT]) {
    struct Vector moveTiles;
    initVector(&moveTiles, KING_MAX_MOVES);
    
    struct BoardMoveHelper moveHelper;
    initBoardMoveHelper(&moveHelper);
    getBoardMoves(self, &moveHelper);

    const int32_t currPlayerId = self->playerId;
    const int32_t opponentId = getOpponentId(currPlayerId);

    const struct BoardPos* currPos = NULL;
    for (int32_t dir = 0; dir < DIRECTION_COUNT; dir++) {
        if (!moveHelper.isDirUsed[dir]) {
            continue;
        }
        
        const size_t size = getSizeVector(&moveHelper.moveDirs[dir]);
        for (size_t elemId = 0; elemId < size; elemId++) {
            currPos = (const struct BoardPos*)getElementVector(
                &moveHelper.moveDirs[dir], elemId);

            struct TileData* tileData = 
                (struct TileData*)malloc(sizeof(struct TileData));
            tileData->tileType = 
                getTileType(currPos, &pieces[currPlayerId], &pieces[opponentId]);
            tileData->boardPos = *currPos;
            
            pushElementVector(&moveTiles, tileData);

            if (tileData->tileType != MOVE_TILE) {
                break;
            }
        }
    }

    deinitBoardMoveHelper(&moveHelper);
    return moveTiles;      
}