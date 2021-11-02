/*      Own include     */
#include "game/entities/pieces/PieceHandler.h"

/*    System includes   */
#include <stdlib.h>

/* Third party includes */

/* Own library includes */
#include "game/proxies/GameBoardProxy.h"
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
            &self->pieces[self->selectedPiecePlayerId], self->selectedPieceId);
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

    for (int32_t i = WHITE_PLAYER_ID; i < PLAYERS_COUNT; i++) {
        const size_t size = getSizeVector(&self->pieces[i]);
        for (size_t pieceId = 0; pieceId < size; pieceId++) {
            currPiece = 
                (struct ChessPiece*)getElementVector(&self->pieces[i], pieceId);
            
            if (!containsEventChessPiece(currPiece, event)) {
                continue;
            }
            
            self->isPieceGrabbed = true;
            self->selectedPieceId = (int32_t)pieceId;
            self->selectedPiecePlayerId = i;
            handlePieceGrabbed(self, currPiece, &event->pos);
            return;
        }
    }
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
                                  cfg->blackPiecesRsrcId, cfg->notReadyFontId)) {
        LOGERR("populatePieces() failed");
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