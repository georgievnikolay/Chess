/*      Own include     */
#include "game/entities/pieces/PieceHandler.h"

/*    System includes   */
#include <stdlib.h>

/* Third party includes */

/* Own library includes */
#include "game/proxies/GameBoardProxy.h"
#include "game/config/PieceHandlerCfg.h"
#include "game/utils/BoardUtils.h"
#include "game/entities/pieces/types//ChessPiece.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

enum PieceHandlerDefines {
    STARTING_PIECES_COUNT = 16,
    PAWNS_COUNT = 8,
    WHITE_PLAYER_START_PAWN_ROW = 6,
    WHITE_PLAYER_START_ROW = 7,
    BLACK_PLAYER_START_PAWN_ROW = 1,
    BLACK_PLAYER_START_ROW = 0,
    NON_PAWN_PIECES_CTN = 8,
    PIECES_IN_A_ROW_CTN = 8,
    ROWS_WITH_PIECES = 2
};

static void doMovePiece(struct ChessPiece* piece, const struct BoardPos* boardPos) {
    setBoardPosChessPiece(piece, boardPos);
}

static void handlePieceGrabbedEvent(struct PieceHandler* self, 
                                    const struct InputEvent* event) {
    if (event->type != TOUCH_RELEASE) {
        return;
    }

    self->isPieceGrabbed = false;
    onPieceUngrabbed(self->gameBoardProxy);
    
    if (!isInsideBoardPoint(&event->pos)) {
        return;
    }

    struct ChessPiece* selectadPiece = (struct ChessPiece*)getElementVector(
            &self->pieces[self->selectedPiecePlayerId], self->selectedPieceId);
    const struct BoardPos boardPos = getBoardPos(&event->pos);
    doMovePiece(selectadPiece, &boardPos);
}

static void handlePieceNoGrabbedEvent(struct PieceHandler* self, 
                                    const struct InputEvent* event) {
    if (event->type != TOUCH_RELEASE) {
        return;
    }

    if (!isInsideBoardPoint(&event->pos)) {
        return;
    }

    struct ChessPiece* currPiece = NULL;

    for (int32_t i = WHITE_PLAYER_ID; i < PLAYERS_COUNT; i++) {
        const size_t size = getSizeVector(&self->pieces[i]);
        for (size_t pieceId = 0; pieceId < size; pieceId++) {
            currPiece = 
                (struct ChessPiece*)getElementVector(&self->pieces[i], pieceId);
            if (containsEventChessPiece(currPiece, event)) {
                self->isPieceGrabbed = true;
                self->selectedPieceId = (int32_t)pieceId;
                self->selectedPiecePlayerId = i;
                const struct BoardPos boardPos = getBoardPos(&event->pos);
                onPieceGrabbed(self->gameBoardProxy, &boardPos);
                return;
            }
        }
    }
}

//TODO Please fix this, there should be a smarter way
static int32_t populatePieces(struct Vector pieces[PLAYERS_COUNT], int32_t whitePiecesRsrcId, int32_t blackPiecesRsrcId) {
    initVector(&pieces[WHITE_PLAYER_ID], STARTING_PIECES_COUNT);
    initVector(&pieces[BLACK_PLAYER_ID], STARTING_PIECES_COUNT);

    const PieceType blackNonPawnTypes[PIECES_IN_A_ROW_CTN] = {
        ROOK, KNIGHT, BISHOP, KING, QUEEN, BISHOP, KNIGHT, ROOK};
    
    const PieceType whiteNonPawnTypes[NON_PAWN_PIECES_CTN] = {
        ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK};
    
    struct ChessPieceCfg pieceCfg;
    struct ChessPiece* currPiece = NULL;
    
    for (int32_t i = 0; i < PAWNS_COUNT; i++) {
        pieceCfg.boardPos.col = i;
        
        pieceCfg.boardPos.row = WHITE_PLAYER_START_PAWN_ROW;
        pieceCfg.playerId = WHITE_PLAYER_ID;
        pieceCfg.rsrcId = whitePiecesRsrcId;
        pieceCfg.pieceType = PAWN;
        
        for (int32_t player = 0; player < PLAYERS_COUNT; player++) {
            currPiece = (struct ChessPiece*)malloc(sizeof(struct ChessPiece));
            if (currPiece == NULL) {
                LOGERR("Bad allocation for chessPiece with rsrcId: %d", i);
                return FAILURE;
            }

            pieceCfg.boardPos.col = i;
            if (SUCCESS != initChessPiece(currPiece, &pieceCfg)) {
                LOGERR("populateWhitePieces() failed rsrdId: %d, relativeId: %d", player, i);
                return FAILURE;
            }

            pushElementVector(&pieces[player], currPiece);        
            
            pieceCfg.boardPos.row = BLACK_PLAYER_START_PAWN_ROW;
            pieceCfg.playerId = BLACK_PLAYER_ID;
            pieceCfg.rsrcId = blackPiecesRsrcId;

        }

        pieceCfg.boardPos.col = i;
        pieceCfg.boardPos.row = WHITE_PLAYER_START_ROW;
        pieceCfg.playerId = WHITE_PLAYER_ID;
        pieceCfg.rsrcId = whitePiecesRsrcId;
        pieceCfg.pieceType = whiteNonPawnTypes[i];

            for (int32_t player = 0; player < PLAYERS_COUNT; player++) {
                currPiece = (struct ChessPiece*)malloc(sizeof(struct ChessPiece));
                if (currPiece == NULL) {
                    LOGERR("Bad allocation for chessPiece with rsrcId: %d", i);
                    return FAILURE;
                }

                pieceCfg.boardPos.col = i;
                if (SUCCESS != initChessPiece(currPiece, &pieceCfg)) {
                    LOGERR("populateWhitePieces() failed rsrdId: %d, relativeId: %d", player, i);
                    return FAILURE;
                }

                pushElementVector(&pieces[player], currPiece);        

                pieceCfg.boardPos.row = BLACK_PLAYER_START_ROW;
                pieceCfg.playerId = BLACK_PLAYER_ID;
                pieceCfg.rsrcId = blackPiecesRsrcId;
                pieceCfg.pieceType = blackNonPawnTypes[i];
        }
    }

    return SUCCESS;
}

int32_t initPieceHandler(struct PieceHandler* self, 
                         const struct PieceHandlerCfg* cfg,
                         void* gameBoardProxy) {
    
    if (NULL == gameBoardProxy) {
        LOGERR("Error, NULL provided for gameBoardProxy");
        return FAILURE;
    }
    self->gameBoardProxy = gameBoardProxy;

    if (SUCCESS != populatePieces(self->pieces, cfg->whitePiecesRsrcId, 
                                                cfg->blackPiecesRsrcId)) {
        LOGERR("populateWhitePieces() failed");
        return FAILURE;
    }

    self->isPieceGrabbed = false;
    self->selectedPieceId = 0;
    self->selectedPiecePlayerId = 0;

    return SUCCESS;
}

void deinitPieceHandler(struct PieceHandler* self) {
    struct ChessPiece* currPiece = NULL;

    for (int32_t i = WHITE_PLAYER_ID; i < PLAYERS_COUNT; i++) {
        const size_t size = getSizeVector(&self->pieces[i]);
        for (size_t pieceId = 0; pieceId < size; pieceId++) {
            currPiece = 
                (struct ChessPiece*)getElementVector(&self->pieces[i], pieceId);
            deinitChessPiece(currPiece);
            free(currPiece);
        }
        freeVector(&self->pieces[i]);
    }
}

void handleEventPieceHandler(struct PieceHandler* self, const struct InputEvent* event) {
    if (self->isPieceGrabbed) {
        handlePieceGrabbedEvent(self, event);
    } else {
        handlePieceNoGrabbedEvent(self, event);
    }
}

void drawPieceHandler(struct PieceHandler* self) {
    struct ChessPiece* currPiece = NULL;

    for (int32_t i = 0; i < PLAYERS_COUNT; i++) {
        const size_t size = getSizeVector(&self->pieces[i]);
        for (size_t pieceId = 0; pieceId < size; pieceId++) {
            currPiece = 
                (struct ChessPiece*)getElementVector(&self->pieces[i], pieceId);
            drawChessPiece(currPiece);
        }
    }
}