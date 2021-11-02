/*      Own include     */
#include "game/entities/pieces/types/Pawn.h"

/*    System includes   */
#include <stdlib.h>

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "game/defines/ChessStructs.h"
#include "game/entities/pieces/types/ChessPiece.h"
#include "game/utils/BoardUtils.h"
#include "game/utils/BoardMoveHelper.h"

/* Forward declarations */

/*        Defines       */

enum PawnDefines {
    PAWN_ALLOWED_DIRS = 3,
    PAWN_ALLOWED_DIAG_DIRS = 2,
    MAX_PAWN_MOVES = 4
};

//TODO: FIX THIS
static void getWhiteBoardMoves(const struct ChessPiece* piece,
                               struct BoardMoveHelper* moveHelper) {
    struct BoardPos* pos = NULL;
    struct BoardPos futurePos;

    const Direction dirs[PAWN_ALLOWED_DIRS] = { UP_LEFT, UP_RIGHT, UP };
    for (int32_t i = 0; i < PAWN_ALLOWED_DIRS; i++) {
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

    //Double pawn move
    if (WHITE_PLAYER_START_PAWN_ROW == piece->boardPos.row) {
        futurePos = getAdjacentPos(UP, &futurePos);
        pos = (struct BoardPos*)malloc(sizeof(struct BoardPos));
        *pos = futurePos;
        pushElementVector(&moveHelper->moveDirs[UP], pos);
    }
}

static void getBlackBoardMoves(const struct ChessPiece* piece,
                               struct BoardMoveHelper* moveHelper) {
    struct BoardPos* pos = NULL;
    struct BoardPos futurePos;

    const Direction dirs[PAWN_ALLOWED_DIRS] = { DOWN_LEFT, DOWN_RIGHT, DOWN };
    for (int32_t i = 0; i < PAWN_ALLOWED_DIRS; i++) {
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

    //Double pawn move
    if (BLACK_PLAYER_START_PAWN_ROW == piece->boardPos.row) {
        futurePos = getAdjacentPos(DOWN, &futurePos);
        pos = (struct BoardPos*)malloc(sizeof(struct BoardPos));
        *pos = futurePos;
        pushElementVector(&moveHelper->moveDirs[DOWN], pos);
    }
}

static struct Vector getWhiteMoveTiles(
        const struct ChessPiece* piece, const struct Vector pieces[PLAYERS_COUNT]) {
    struct BoardMoveHelper moveHelper;
    initBoardMoveHelper(&moveHelper);
    getWhiteBoardMoves(piece, &moveHelper);

    const int32_t opponentId = getOpponentId(piece->playerId);
    struct Vector* currMoveDir = NULL;
    struct BoardPos* currBoardPos = NULL;

    struct Vector moveTiles;
    initVector(&moveTiles, MAX_PAWN_MOVES);

    currMoveDir = &moveHelper.moveDirs[UP];
    { // local scope
        const size_t dirElems = getSizeVector(currMoveDir);
        for (size_t i = 0; i < dirElems; i++) {
            currBoardPos = (struct BoardPos*)getElementVector(currMoveDir, i);

            const TileType tileType = 
                getTileType(currBoardPos, &pieces[piece->playerId], &pieces[opponentId]);
            
            if (tileType != MOVE_TILE) {
                break;
            }

            struct TileData* tileData = 
                    (struct TileData*)malloc(sizeof(struct TileData));
            tileData->boardPos = *currBoardPos;
            tileData->tileType = tileType;
            pushElementVector(&moveTiles, (void*)tileData);
        }
    }

    const Direction dirs[PAWN_ALLOWED_DIAG_DIRS] = {UP_LEFT, UP_RIGHT };
    for (int32_t dir = 0; dir < PAWN_ALLOWED_DIAG_DIRS; dir++) {
        const Direction currDir = dirs[dir];
        currMoveDir = &moveHelper.moveDirs[currDir];

        const size_t dirElems = getSizeVector(currMoveDir);
        for (size_t i = 0; i < dirElems; i++) {
            currBoardPos = (struct BoardPos*)getElementVector(currMoveDir, i);

            const TileType tileType = 
                    getTileType(currBoardPos, &pieces[piece->playerId], &pieces[opponentId]);

            if (tileType == MOVE_TILE) {
                break;
            }

            struct TileData* tileData = 
                    (struct TileData*)malloc(sizeof(struct TileData));
            tileData->boardPos = *currBoardPos;
            tileData->tileType = tileType;
            pushElementVector(&moveTiles, (void*)tileData);
        }
    }

    deinitBoardMoveHelper(&moveHelper);
    return moveTiles;
}

static struct Vector getBlackMoveTiles(
        const struct ChessPiece* piece, const struct Vector pieces[PLAYERS_COUNT]) {
    struct BoardMoveHelper moveHelper;
    initBoardMoveHelper(&moveHelper);
    getBlackBoardMoves(piece, &moveHelper);

    const int32_t opponentId = getOpponentId(piece->playerId);
    struct Vector* currMoveDir = NULL;
    struct BoardPos* currBoardPos = NULL;

    struct Vector moveTiles;
    initVector(&moveTiles, MAX_PAWN_MOVES);

    currMoveDir = &moveHelper.moveDirs[DOWN];
    { // local scope
        const size_t dirElems = getSizeVector(currMoveDir);
        for (size_t i = 0; i < dirElems; i++) {
            currBoardPos = (struct BoardPos*)getElementVector(currMoveDir, i);

            const TileType tileType = 
                getTileType(currBoardPos, &pieces[piece->playerId], &pieces[opponentId]);
            
            if (tileType != MOVE_TILE) {
                break;
            }

            struct TileData* tileData = 
                    (struct TileData*)malloc(sizeof(struct TileData));
            tileData->boardPos = *currBoardPos;
            tileData->tileType = tileType;
            pushElementVector(&moveTiles, (void*)tileData);
        }
    }

    const Direction dirs[PAWN_ALLOWED_DIAG_DIRS] = {DOWN_LEFT, DOWN_RIGHT };
    for (int32_t dir = 0; dir < PAWN_ALLOWED_DIAG_DIRS; dir++) {
        const Direction currDir = dirs[dir];
        currMoveDir = &moveHelper.moveDirs[currDir];

        const size_t dirElems = getSizeVector(currMoveDir);
        for (size_t i = 0; i < dirElems; i++) {
            currBoardPos = (struct BoardPos*)getElementVector(currMoveDir, i);

            const TileType tileType = 
                    getTileType(currBoardPos, &pieces[piece->playerId], &pieces[opponentId]);

            if (tileType == MOVE_TILE) {
                break;
            }

            struct TileData* tileData = 
                    (struct TileData*)malloc(sizeof(struct TileData));
            tileData->boardPos = *currBoardPos;
            tileData->tileType = tileType;
            pushElementVector(&moveTiles, (void*)tileData);
        }
    }
    
    deinitBoardMoveHelper(&moveHelper);
    return moveTiles;
}
struct Vector getMoveTilesPawn(const struct ChessPiece* piece, 
                               const struct Vector pieces[PLAYERS_COUNT]) {
    if (WHITE_PLAYER_ID == piece->playerId) {
        return getWhiteMoveTiles(piece, pieces);
    }

    return getBlackMoveTiles(piece, pieces);
}