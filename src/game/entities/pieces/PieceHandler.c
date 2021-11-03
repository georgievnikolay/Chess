/*      Own include     */
#include "game/entities/pieces/PieceHandler.h"

/*    System includes   */
#include <stdlib.h>

/* Third party includes */

/* Own library includes */
#include "game/proxies/GameBoardProxy.h"
#include "game/proxies/GameProxy.h"
#include "game/config/PieceHandlerCfg.h"
#include "game/utils/BoardUtils.h"
#include "game/entities/pieces/types/ChessPiece.h"
#include "game/entities/pieces/PieceHandlerPopulator.h"
#include "game/entities/pieces/ChessPieceResolver.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

static void doMovePiece(struct PieceHandler* self, 
                        struct ChessPiece* piece,
                        const struct BoardPos* selectedBoardPos) {

    setBoardPosChessPieceResolver(piece, selectedBoardPos);
    const int32_t opponentId = getOpponentId(piece->playerId);
    int32_t foundIdx = -1;

    if (doCollideWithPiece(selectedBoardPos, &self->pieces[opponentId], &foundIdx)) {
        struct ChessPiece* enemyPiece = 
                getElementVector(&self->pieces[opponentId], foundIdx);
        deinitChessPieceResolver(enemyPiece);
        free(enemyPiece);
        deleteElementVector(&self->pieces[opponentId], foundIdx);
    }

    finishTurnGameProxy(self->gameProxy);
}

static void handlePieceGrabbed(struct PieceHandler* self,
                               struct ChessPiece* selectedPiece,
                               const struct Point* pos) {

    const struct BoardPos boardPos = getBoardPos(pos);
    const struct Vector moveTile = 
            getMoveTilesPieceResolver(selectedPiece, self->pieces);
    
    onPieceGrabbedGameBoardProxy(self->gameBoardProxy, &boardPos, &moveTile);
}

static void handlePieceGrabbedEvent(struct PieceHandler* self, 
                                    const struct InputEvent* event) {
    if (event->type != TOUCH_RELEASE) {
        return;
    }

    self->isPieceGrabbed = false;
    
    if (!isInsideBoardPoint(&event->pos)) {
        onPieceUngrabbedGameBoardProxy(self->gameBoardProxy);
        return;
    }

    const struct BoardPos boardPos = getBoardPos(&event->pos);
    if (!isMoveAllowedGameBoardProxy(self->gameBoardProxy, &boardPos)) {
        onPieceUngrabbedGameBoardProxy(self->gameBoardProxy);
        return;
    }
    onPieceUngrabbedGameBoardProxy(self->gameBoardProxy);

    struct ChessPiece* selectedPiece = (struct ChessPiece*)getElementVector(
            &self->pieces[self->currPlayerId], self->selectedPieceId);
    doMovePiece(self, selectedPiece, &boardPos);
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

    const size_t size = getSizeVector(&self->pieces[self->currPlayerId]);
    for (size_t pieceId = 0; pieceId < size; pieceId++) {
        currPiece = 
            (struct ChessPiece*)getElementVector(
                &self->pieces[self->currPlayerId], pieceId);
        
        if (!containsEventChessPiece(currPiece, event)) {
            continue;
        }
        
        self->isPieceGrabbed = true;
        self->selectedPieceId = (int32_t)pieceId;
        handlePieceGrabbed(self, currPiece, &event->pos);
        return;
    }
}

int32_t initPieceHandler(struct PieceHandler* self, 
                         const struct PieceHandlerCfg* cfg,
                         int32_t startingPlayerId,
                         void* gameProxy, void* gameBoardProxy) {
    
    if (NULL == gameBoardProxy) {
        LOGERR("Error, NULL provided for gameBoardProxy");
        return FAILURE;
    }
    self->gameBoardProxy = gameBoardProxy;

    if (NULL == gameProxy) {
        LOGERR("Error, NULL provided for gameProxy");
        return FAILURE;
    }
    self->gameProxy = gameProxy;

    if (SUCCESS != populatePieces(self->pieces, cfg->whitePiecesRsrcId, 
                                  cfg->blackPiecesRsrcId, cfg->notReadyFontId, gameProxy)) {
        LOGERR("populatePieces() failed");
        return FAILURE;
    }

    self->isPieceGrabbed = false;
    self->selectedPieceId = 0;
    self->currPlayerId = startingPlayerId;

    return SUCCESS;
}

void deinitPieceHandler(struct PieceHandler* self) {
    struct ChessPiece* currPiece = NULL;

    for (int32_t i = WHITE_PLAYER_ID; i < PLAYERS_COUNT; i++) {
        const size_t size = getSizeVector(&self->pieces[i]);
        for (size_t pieceId = 0; pieceId < size; pieceId++) {
            currPiece = 
                (struct ChessPiece*)getElementVector(&self->pieces[i], pieceId);
            deinitChessPieceResolver(currPiece);
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
            drawChessPieceResolver(currPiece);
        }
    }
}


void promotePiecePieceHandler(struct PieceHandler* self, PieceType pieceType) {
    //Have to get the opposite player because after the move its instantly the other player
    const int32_t currPlayerId = getOpponentId(self->currPlayerId);
    int32_t currPieceIdx = self->selectedPieceId;
    
    struct ChessPiece* currPiece = 
        getElementVector(&self->pieces[currPlayerId], currPieceIdx);
    
    struct ChessPieceCfg pieceCfg;
    pieceCfg.pieceType = pieceType;
    pieceCfg.boardPos = currPiece->boardPos;
    pieceCfg.playerId = currPiece->playerId;

    //TODO: how to get the texture?
    pieceCfg.rsrcId = currPlayerId;

    //TODO: unfinished
    bool isUnfinished = true;
    if (pieceType == ROOK || 
        pieceType == BISHOP) {
        isUnfinished = false;
    }
    int32_t notReadyFontId = 0; //Angeline vintage font with size 20
    
    deinitChessPieceResolver(currPiece);
    free(currPiece);
    deleteElementVector(&self->pieces[currPlayerId], currPieceIdx);

    promoteChessPiecePieceResolver(&pieceCfg, notReadyFontId, isUnfinished, &currPiece);

    pushElementVector(&self->pieces[currPlayerId], currPiece);
}

static void mirrorBoardPos(struct BoardPos* currBoardPos) {
    const int32_t boardColsAndRows = BOARD_ROWS_COLS;
    currBoardPos->row = boardColsAndRows - currBoardPos->row;
    currBoardPos->col = boardColsAndRows - currBoardPos->col;
}

void invertPieces(struct Vector pieces[PLAYERS_COUNT]) {
    for (int32_t playerId = 0; playerId < PLAYERS_COUNT; playerId++) {
        const size_t size = getSizeVector(&pieces[playerId]);
        for (size_t i = 0; i < size; i++) {
            struct ChessPiece* currPiece = 
                (struct ChessPiece*)getElementVector(&pieces[playerId], i);
            mirrorBoardPos(&currPiece->boardPos);
            setBoardPosChessPiece(currPiece, &currPiece->boardPos);
        }
    }
}

