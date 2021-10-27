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
    TILES_IN_ROW = 8,
    TILES_IN_COL = 8,
    BOARD_MID = 4,
    NONE = -1
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

    struct ChessPiece* selectedPiece = (struct ChessPiece*)getElementVector(
            &self->pieces[self->selectedPiecePlayerId], self->selectedPieceId);
    const struct BoardPos boardPos = getBoardPos(&event->pos);
    doMovePiece(selectedPiece, &boardPos);
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

static int32_t insertChessPiece(struct Vector* player, const struct ChessPieceCfg* pieceCfg) {
    struct ChessPiece* currPiece = NULL;
    currPiece = (struct ChessPiece*)malloc(sizeof(struct ChessPiece));
    if (currPiece == NULL) {
        LOGERR("Bad allocation for chessPiece at [%d,%d].",
                pieceCfg->boardPos.row, pieceCfg->boardPos.col);
        return FAILURE;
    }

    if (SUCCESS != initChessPiece(currPiece, pieceCfg)) {
        LOGERR("initChessPiece() failed rsrdId: %d", pieceCfg->rsrcId);
        return FAILURE;
    }

    pushElementVector(player, currPiece);

    return SUCCESS;      
}

//TODO Please fix this, there should be a smarter way
static int32_t populatePieces(struct Vector pieces[PLAYERS_COUNT], int32_t whitePiecesRsrcId, int32_t blackPiecesRsrcId) {
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

            if (SUCCESS != insertChessPiece(&pieces[pieceCfg.playerId], 
                                            &pieceCfg)) {
                LOGERR("Error, insertChessPiece() failed");
                return FAILURE;
            }
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