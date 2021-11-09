/*      Own include     */
#include "game/entities/pieces/types/Pawn.h"

/*    System includes   */
#include <stdlib.h>

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "game/defines/ChessStructs.h"
#include "game/proxies/GameProxy.h"
#include "game/utils/BoardUtils.h"
#include "game/utils/BoardMoveHelper.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

enum PawnDefines {
    PAWN_ALLOWED_DIRS = 3,
    PAWN_ALLOWED_DIAG_DIRS = 2,
    MAX_PAWN_MOVES = 4,

    PLAYER_EN_PASSANT_ROW = 4,
};

/* BEGIN EN PASSANT SPECIFIC FUNTIONS */

/* Before we take  the moveTiles for the current move of the Pawn 
we want to reset the enemy Pawn(if any) that was in En Passant 2 moves ago*/
static void resetPawnsEnPassantStats(struct Vector* enemyPieces) {
    struct ChessPiece* piece = NULL;
    size_t size = getSizeVector(enemyPieces);

    for (size_t i = 0; i < size; i++) {
        piece = getElementVector(enemyPieces, i);
        
        if (piece->pieceType == PAWN) {
            struct Pawn* pawn = (struct Pawn*)piece;

            /* if En Passant was activated 2 moves ago, deactivate it*/
            if (pawn->enPassantActivatedMove + 2 == 
                    getNumberOfMovesGameProxy(pawn->gameProxy)) {
                pawn->isInEnPassant = false;
                return;        
            }
        }
    }
}

/* If on the left or the right side of the curr Pawn 
there is another Pawn that is in en passant 
then we want to make the UP_LEFT/UP_RIGHT tileType = TAKE_TILE */
static bool hasAdjacentEnPassantPawn(const struct BoardPos* currAttackedBoardPos, const struct Vector* enemyPieces) {
    const struct BoardPos adjacentEnemy = { .col = currAttackedBoardPos->col,
                                            .row = (currAttackedBoardPos->row + 1) };

    const size_t size = getSizeVector(enemyPieces);
    struct ChessPiece* currEnemyPiece = NULL;
    for (size_t i = 0; i < size; i++) {
        currEnemyPiece = getElementVector(enemyPieces, i);

        if (currEnemyPiece->pieceType == PAWN) {
            struct Pawn* pawn = (struct Pawn*)currEnemyPiece;
            if (pawn->isInEnPassant) {
                if (areBoardPosEqual(&pawn->base.boardPos, &adjacentEnemy)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool doCollideWithPiecePawn(const struct BoardPos *selectedPos,
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

        /* If enemy Pawn is in En Passant and selectedPos is the tile behind it
        *  Then we can take it and return its index so it can be deinitialised
        */
        if (piece->pieceType == PAWN) {
            const struct Pawn* pawn = (const struct Pawn*)piece;
            if (pawn->isInEnPassant) {
                const struct BoardPos enPassantPos = { .col = pawn->base.boardPos.col,
                                                       .row = (pawn->base.boardPos.row - 1)};
                if (areBoardPosEqual(selectedPos, &enPassantPos)) {
                    if (getNumberOfMovesGameProxy(pawn->gameProxy) == (pawn->enPassantActivatedMove + 1)) {
                        *outCollisionRelativeId = (int32_t)i;
                        return true;
                    }
                }
            }
        }
    }

    *outCollisionRelativeId = -1;
    return false;
}
/* END EN PASSANT SPECIFIC FUNTIONS */

static void getBoardMoves(const struct ChessPiece* piece,
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
    if (PLAYER_START_PAWN_ROW == piece->boardPos.row) {
        futurePos = getAdjacentPos(UP, &futurePos);
        pos = (struct BoardPos*)malloc(sizeof(struct BoardPos));
        *pos = futurePos;
        pushElementVector(&moveHelper->moveDirs[UP], pos);
    }
}

static struct Vector getMoveTiles(
        const struct ChessPiece* piece, struct Vector pieces[PLAYERS_COUNT]) {
    struct BoardMoveHelper moveHelper;
    initBoardMoveHelper(&moveHelper);
    getBoardMoves(piece, &moveHelper);

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

    /* Reset enemy Pawn with obsolite En Passant 
    before getting diagonal moveTiles*/
    resetPawnsEnPassantStats(&pieces[opponentId]);

    const Direction dirs[PAWN_ALLOWED_DIAG_DIRS] = { UP_LEFT, UP_RIGHT };
    for (int32_t dir = 0; dir < PAWN_ALLOWED_DIAG_DIRS; dir++) {
        const Direction currDir = dirs[dir];
        currMoveDir = &moveHelper.moveDirs[currDir];

        const size_t dirElems = getSizeVector(currMoveDir);
        for (size_t i = 0; i < dirElems; i++) {
            currBoardPos = (struct BoardPos*)getElementVector(currMoveDir, i);

            TileType tileType;
            if (hasAdjacentEnPassantPawn(currBoardPos, &pieces[opponentId])) {
                tileType = TAKE_TILE;
            } else {
                tileType = 
                    getTileType(currBoardPos, &pieces[piece->playerId], &pieces[opponentId]);   
            }

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

int32_t initPawn(struct Pawn* self, const struct ChessPieceCfg* cfg, 
                 void* gameProxy) {
    if (initChessPiece(&self->base, cfg)) {
        LOGERR("Error, initChessPiece() failed for rsrcId: %d", cfg->rsrcId);
        return FAILURE;
    }

    if (NULL == gameProxy) {
        LOGERR("Error, NULL provided for gameProxy");
        return FAILURE;
    }
    self->gameProxy = gameProxy;

    /*
    * movesCount: stores how many moves Pawn has made
    * isInEnPassant: tells if Pawn is in En Passant
    * enPassantActivatedMove: stores on which move of the game 
    *                         the En Passant for the specific Pawn was activated
    */
    self->movesCount = 0;
    self->isInEnPassant =false;
    self->enPassantActivatedMove = 0;

    return SUCCESS;
}

void setBoardPosPawn(struct Pawn* self, const struct BoardPos* boardPos) {
    setBoardPosChessPiece(&self->base, boardPos);

    if (PLAYER_END_PAWN_ROW == boardPos->row) {
        activatePawnPromotionGameProxy(self->gameProxy);
        return;
    }

    self->movesCount += 1;
    
    if (PLAYER_EN_PASSANT_ROW == self->base.boardPos.row 
        && self->movesCount == 1) {
            
        self->enPassantActivatedMove = 
            getNumberOfMovesGameProxy(self->gameProxy);
        self->isInEnPassant = true;
    } else {
        self->isInEnPassant = false;
    }
}

struct Vector getMoveTilesPawn(const struct ChessPiece* self, 
                               struct Vector pieces[PLAYERS_COUNT]) {
    return getMoveTiles(self, pieces);
}