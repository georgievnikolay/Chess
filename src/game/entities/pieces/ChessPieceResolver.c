/*      Own include     */
#include "game/entities/pieces/ChessPieceResolver.h"

/*    System includes   */
#include <stdlib.h>

/* Third party includes */

/* Own library includes */
#include "game/entities/pieces/types/UnfinishedPiece.h"
#include "game/entities/pieces/types/Rook.h"
#include "game/entities/pieces/types/Pawn.h"
#include "game/entities/pieces/types/Bishop.h"
#include "game/utils/BoardPos.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
/* Forward declarations */

/*        Defines       */

void setBoardPosChessPieceResolver(struct ChessPiece* piece, 
                                   const struct BoardPos* boardPos) {
    if (piece->isUnfinished) {
        setBoardPosUnfinishedPiece((struct UnfinishedPiece*)piece, boardPos);
        return;
    }

    switch (piece->pieceType) {
        case PAWN:
            setBoardPosPawn((struct Pawn*)piece, boardPos);
            break;

        case KING:
        case QUEEN:
        case BISHOP:
        case KNIGHT:
        case ROOK:
            setBoardPosChessPiece(piece, boardPos);
            break;
        default:
            LOGERR("Error, recieved unsupported pieceType: %d", piece->pieceType);
            break;
    }
}

void deinitChessPieceResolver(struct ChessPiece* piece) {
    if (piece->isUnfinished) {
        deinitUnfinishedPiece((struct UnfinishedPiece*)piece);
        return;
    }

    switch (piece->pieceType) {
        case KING:
        case QUEEN:
        case BISHOP:
        case KNIGHT:
        case ROOK:
        case PAWN:
            deinitChessPiece(piece);
            break;
        default:
            LOGERR("Error, recieved unsupported pieceType: %d", piece->pieceType);
            break;
    }
}

void drawChessPieceResolver(struct ChessPiece* piece) {
    if (piece->isUnfinished) {
        drawUnfinishedPiece((struct UnfinishedPiece*)piece);
        return;
    }

    switch (piece->pieceType) {
        case KING:
        case QUEEN:
        case BISHOP:
        case KNIGHT:
        case ROOK:
        case PAWN:
            drawChessPiece(piece);
            break;
        default:
            LOGERR("Error, recieved unsupported pieceType: %d", piece->pieceType);
            break;
    }
}

struct Vector getMoveTilesPieceResolver(
    struct ChessPiece* piece, const struct Vector pieces[PLAYERS_COUNT]) {

    if (piece->isUnfinished) {
        return getMoveTilesUnfinishedPiece((struct UnfinishedPiece*)piece, pieces);
    }

    switch (piece->pieceType) {
        case ROOK:
            return getMoveTilesRook(piece, pieces);
            break;
        
        case PAWN:
            return getMoveTilesPawn(piece, pieces);
            break;
        
        case BISHOP:
            return getMoveTilesBishop(piece, pieces);
            break;

        case KING:
        case QUEEN:
        case KNIGHT:
            break;
        default:
            LOGERR("Error, recieved unsupported pieceType: %d", piece->pieceType);
            break;
    }

    struct Vector moveTiles;
    initVector(&moveTiles, 0);
    return moveTiles;
}

int32_t initChessPieceResolver(const struct ChessPieceCfg* cfg, 
                               int32_t notReadyFontId,
                               bool isUnfinished, void* gameProxy,
                               struct ChessPiece** outPiece) {
    if (isUnfinished) {
        struct UnfinishedPiece* currPiece = NULL;
        currPiece = (struct UnfinishedPiece*)malloc(sizeof(struct UnfinishedPiece));
        if (currPiece == NULL) {
            LOGERR("Bad allocation for chessPiece at [%d,%d].",
                cfg->boardPos.row, cfg->boardPos.col);
            return FAILURE;
        }
        
        if (SUCCESS != initUnfinishedPiece(currPiece, cfg, notReadyFontId)) {
            LOGERR("initUnfinishedPiece() failed rsrdId: %d", cfg->rsrcId);
            return FAILURE;
        }

        *outPiece = (struct ChessPiece*)currPiece;
        return SUCCESS;
    }

    switch (cfg->pieceType) {
        case PAWN: {
            struct Pawn* currPiece = NULL;
            currPiece = (struct Pawn*)malloc(sizeof(struct Pawn));
            if (currPiece == NULL) {
                LOGERR("Bad allocation for chessPiece at [%d,%d].",
                    cfg->boardPos.row, cfg->boardPos.col);
                return FAILURE;
            }
        
            if (SUCCESS != initPawn(currPiece, cfg, gameProxy)) {
                LOGERR("initUnfinishedPiece() failed rsrdId: %d", cfg->rsrcId);
                return FAILURE;
            }

            *outPiece = (struct ChessPiece*)currPiece;
        }            
            break;

        case BISHOP:
        case ROOK: {
            struct ChessPiece* currPiece = NULL;
            currPiece = (struct ChessPiece*)malloc(sizeof(struct ChessPiece));
            if (currPiece == NULL) {
                LOGERR("Bad allocation for chessPiece at [%d,%d].",
                    cfg->boardPos.row, cfg->boardPos.col);
                return FAILURE;
            }
        
            if (SUCCESS != initChessPiece(currPiece, cfg)) {
                LOGERR("initUnfinishedPiece() failed rsrdId: %d", cfg->rsrcId);
                return FAILURE;
            }

            *outPiece = currPiece;
        }            
            break;

        case KING:
        case QUEEN:
        case KNIGHT:
            LOGERR("Error, pieceType: %d is not implemented", (*outPiece)->pieceType);
            return FAILURE;
        default:
            LOGERR("Error, recieved unsupported pieceType: %d", (*outPiece)->pieceType);
            return FAILURE;
            break;
    }

    return SUCCESS;
}

int32_t promoteChessPiecePieceResolver(const struct ChessPieceCfg* cfg, 
                               int32_t notReadyFontId,
                               bool isUnfinished,
                               struct ChessPiece** outPiece) {
    
    if (isUnfinished) {
        struct UnfinishedPiece* currPiece = NULL;
        currPiece = (struct UnfinishedPiece*)malloc(sizeof(struct UnfinishedPiece));
        if (currPiece == NULL) {
            LOGERR("Bad allocation for chessPiece at [%d,%d].",
                cfg->boardPos.row, cfg->boardPos.col);
            return FAILURE;
        }
        
        if (SUCCESS != initUnfinishedPiece(currPiece, cfg, notReadyFontId)) {
            LOGERR("initUnfinishedPiece() failed rsrdId: %d", cfg->rsrcId);
            return FAILURE;
        }

        *outPiece = (struct ChessPiece*)currPiece;
        return SUCCESS;
    }

    switch (cfg->pieceType) {
        case BISHOP:
        case ROOK: {
            struct ChessPiece* currPiece = NULL;
            currPiece = (struct ChessPiece*)malloc(sizeof(struct ChessPiece));
            if (currPiece == NULL) {
                LOGERR("Bad allocation for chessPiece at [%d,%d].",
                    cfg->boardPos.row, cfg->boardPos.col);
                return FAILURE;
            }
        
            if (SUCCESS != initChessPiece(currPiece, cfg)) {
                LOGERR("initUnfinishedPiece() failed rsrdId: %d", cfg->rsrcId);
                return FAILURE;
            }

            *outPiece = currPiece;
        }            
            break;

        case QUEEN:
        case KNIGHT:
            LOGERR("Error, pieceType: %d is not implemented", (*outPiece)->pieceType);
            return FAILURE;
        default:
            LOGERR("Error, recieved unsupported pieceType: %d", (*outPiece)->pieceType);
            return FAILURE;
            break;
    }

    return SUCCESS;
}