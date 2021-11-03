/*      Own include     */
#include "game/entities/pieces/types/Bishop.h"

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

enum BishopDefines {
    BISHOP_ALLOWED_DIRS = 4,
    BISHOP_MAX_MOVES = 13
};

static void getBoardMoves(const struct ChessPiece *piece,
                          struct BoardMoveHelper *moveHelper) {

    const Direction dirs[BISHOP_ALLOWED_DIRS] = { 
        UP_LEFT, UP_RIGHT, DOWN_RIGHT, DOWN_LEFT };

    for (int32_t i = 0; i < BISHOP_ALLOWED_DIRS; i++) {
        const Direction currDir = dirs[i];
        moveHelper->isDirUsed[currDir] = true;

        struct BoardPos futurePos = getAdjacentPos(currDir, &piece->boardPos);
        while (isInsideBoardBoardPos(&futurePos)) {
 
            struct BoardPos* boardPos = 
                    (struct BoardPos*)malloc(sizeof(struct BoardPos));
            
            *boardPos = futurePos;
            pushElementVector(&moveHelper->moveDirs[currDir], boardPos);

            futurePos = getAdjacentPos(currDir, &futurePos);
        }
    }
}

struct Vector getMoveTilesBishop(const struct ChessPiece* self, 
                                 const struct Vector pieces[PLAYERS_COUNT]) {
    struct Vector moveTiles;
    initVector(&moveTiles, BISHOP_MAX_MOVES);
    
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