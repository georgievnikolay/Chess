/*      Own include     */
#include "game/entities/pieces/types/Knight.h"

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

enum KnightDefines {
    KNIGHT_ALLOWED_DIRS = 8,
    KNIGHT_MAX_MOVES = 8
};

static void getBoardMoves(const struct ChessPiece *piece,
                          struct BoardMoveHelper *moveHelper) {
    struct BoardPos futurePos;

    const Direction dirs[KNIGHT_ALLOWED_DIRS] = { 
        KNIGHT_UP_LEFT_LOWER, KNIGHT_UP_LEFT_UPPER, 
        KNIGHT_UP_RIGHT_LOWER, KNIGHT_UP_RIGHT_UPPER,
        KNIGHT_DOWN_LEFT_LOWER, KNIGHT_DOWN_LEFT_UPPER,
        KNIGHT_DOWN_RIGHT_LOWER, KNIGHT_DOWN_RIGHT_UPPER};

    for (int32_t i = 0; i < KNIGHT_ALLOWED_DIRS; i++) {
        const Direction currDir = dirs[i];
        futurePos = getAdjacentPos(currDir, &piece->boardPos);
        
        if (!isInsideBoardBoardPos(&futurePos)) {
            continue;
        }

        moveHelper->isDirUsed[currDir] = true;
        struct BoardPos* boardPos = 
            (struct BoardPos*)malloc(sizeof(struct BoardPos));

        *boardPos = futurePos;
        pushElementVector(&moveHelper->moveDirs[currDir], boardPos);
    }
}

struct Vector getMoveTilesKnight(const struct ChessPiece* self, 
                                 const struct Vector pieces[PLAYERS_COUNT]) {
    struct Vector moveTiles;
    initVector(&moveTiles, KNIGHT_MAX_MOVES);
    
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
        }
    }

    deinitBoardMoveHelper(&moveHelper);
    return moveTiles;  
}