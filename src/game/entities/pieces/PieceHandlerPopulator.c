/*      Own include     */
#include "game/entities/pieces/PieceHandlerPopulator.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "game/config/PieceHandlerCfg.h"
#include "game/entities/pieces/ChessPieceResolver.h"
#include "game/entities/pieces/types/ChessPiece.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

//maybe move to resolver
static int32_t insertChessPiece(struct Vector* player, void* gameProxy,
                                const struct ChessPieceCfg* pieceCfg) {
    struct ChessPiece* currPiece = NULL;

    if (SUCCESS != initChessPieceResolver(pieceCfg, gameProxy, &currPiece)) {
        LOGERR("initChessPieceResolver() failed rsrdId: %d", pieceCfg->rsrcId);
        return FAILURE;        
    }
    pushElementVector(player, currPiece);

    return SUCCESS;      
}

int32_t populatePieces(struct Vector pieces[PLAYERS_COUNT], 
                       int32_t whitePiecesRsrcId, 
                       int32_t blackPiecesRsrcId, 
                       void* gameProxy) {

    initVector(&pieces[WHITE_PLAYER_ID], STARTING_PIECES_COUNT);
    initVector(&pieces[BLACK_PLAYER_ID], STARTING_PIECES_COUNT);

    const PieceType allPieces[TILES_IN_ROW][TILES_IN_COL] = {
        {ROOK, KNIGHT, BISHOP, KING, QUEEN, BISHOP, KNIGHT, ROOK},
        {PAWN, PAWN,   PAWN,   PAWN, PAWN,  PAWN,   PAWN,   PAWN},
        {NONE, NONE,   NONE,   NONE, NONE,  NONE,   NONE,   NONE},
        {NONE, NONE,   NONE,   NONE, NONE,  NONE,   NONE,   NONE},
        {NONE, NONE,   NONE,   NONE, NONE,  NONE,   NONE,   NONE},
        {NONE, NONE,   NONE,   NONE, NONE,  NONE,   NONE,   NONE},
        {PAWN, PAWN,   PAWN,   PAWN, PAWN,  PAWN,   PAWN,   PAWN},
        {ROOK, KNIGHT, BISHOP, KING, QUEEN, BISHOP, KNIGHT, ROOK}
    };
    
    struct ChessPieceCfg pieceCfg;
    
    for (int32_t row = 0; row < TILES_IN_ROW; ++row) {
        pieceCfg.boardPos.row = row;
        
        if (row < BOARD_MID) {
            pieceCfg.playerId = BLACK_PLAYER_ID;
            pieceCfg.rsrcId = blackPiecesRsrcId;
        } else {
            pieceCfg.playerId = WHITE_PLAYER_ID;
            pieceCfg.rsrcId = whitePiecesRsrcId;
        }

        for (int32_t col = 0; col < TILES_IN_COL; ++col) {
            pieceCfg.boardPos.col = col;

            pieceCfg.pieceType = allPieces[row][col];
            if (pieceCfg.pieceType == (PieceType)NONE) {
                continue;
            }

            if (SUCCESS != insertChessPiece(&pieces[pieceCfg.playerId], gameProxy,
                                            &pieceCfg)) {
                LOGERR("Error, insertChessPiece() failed");
                return FAILURE;
            }
        }
    }

    return SUCCESS;
}