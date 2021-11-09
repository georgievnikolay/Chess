/*      Own include     */
#include "game/entities/pieces/ChessPieceResolver.h"

/*    System includes   */
#include <stdlib.h>

/* Third party includes */

/* Own library includes */
#include "game/entities/pieces/types/Rook.h"
#include "game/entities/pieces/types/Pawn.h"
#include "game/entities/pieces/types/Bishop.h"
#include "game/entities/pieces/types/Queen.h"
#include "game/entities/pieces/types/King.h"
#include "game/entities/pieces/types/Knight.h"
#include "game/utils/BoardPos.h"
#include "game/utils/BoardUtils.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

void setBoardPosChessPieceResolver(struct ChessPiece* piece, 
                                   const struct BoardPos* boardPos) {

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

    switch (piece->pieceType) {
        case KING:
        case QUEEN:
        case BISHOP:
        case KNIGHT:
        case ROOK:
        case PAWN:
            drawChessPiece(piece);
            break;
        case NONE:
            break;
        default:
            LOGERR("Error, recieved unsupported pieceType: %d", piece->pieceType);
            break;
    }
}

struct Vector getMoveTilesPieceResolver(
    struct ChessPiece* piece, struct Vector pieces[PLAYERS_COUNT]) {

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

        case QUEEN:
            return getMoveTilesQueen(piece, pieces);
            break;

        case KING:
            return getMoveTilesKing(piece, pieces);
            break;

        case KNIGHT:
            return getMoveTilesKnight(piece, pieces);
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
                               void* gameProxy,
                               struct ChessPiece** outPiece) {

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
                LOGERR("initPawn() failed rsrdId: %d", cfg->rsrcId);
                return FAILURE;
            }

            *outPiece = (struct ChessPiece*)currPiece;
        }            
            break;

        case KING:
        case QUEEN:
        case KNIGHT:
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
                LOGERR("initChessPiece() failed rsrdId: %d", cfg->rsrcId);
                return FAILURE;
            }

            *outPiece = currPiece;
        }            
            break;

        default:
            LOGERR("Error, recieved unsupported pieceType: %d", cfg->pieceType);
            return FAILURE;
            break;
    }

    return SUCCESS;
}

int32_t promoteChessPiecePieceResolver(const struct ChessPieceCfg* cfg, 
                                       struct ChessPiece** outPiece) {

    switch (cfg->pieceType) {
        case KNIGHT:
        case QUEEN:
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
                LOGERR("initChessPiece() failed rsrdId: %d", cfg->rsrcId);
                return FAILURE;
            }

            *outPiece = currPiece;
        }            
            break;

        default:
            LOGERR("Error, recieved unsupported pieceType: %d", (*outPiece)->pieceType);
            return FAILURE;
            break;
    }

    return SUCCESS;
}

bool doCollideWithPieceChessPieceResolver(const struct BoardPos *selectedPos,
                                          struct ChessPiece* piece,
                                          const struct Vector *pieces,
                                          int32_t *outCollisionRelativeId) {
    
    switch (piece->pieceType) {
        case PAWN:
            return doCollideWithPiecePawn(selectedPos, pieces, outCollisionRelativeId);
            break;

        case KING:
        case QUEEN:
        case BISHOP:
        case KNIGHT:
        case ROOK:
            return doCollideWithPiece(selectedPos, pieces, outCollisionRelativeId);
            break;
        default:
            LOGERR("Error, recieved unsupported pieceType: %d", piece->pieceType);
            break;
    }

    return false;    
}