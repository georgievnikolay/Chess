/*      Own include     */
#include "game/Game.h"

/*    System includes   */
#include <stdbool.h>
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "game/entities/GameStatePanel.h"
#include "game/entities/LogPanel.h"
#include "game/entities/pieces/types/ChessPiece.h"
#include "game/defines/ChessDefines.h"
#include "game/proxies/GameProxy.h"
#include "utils/drawing/Color.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

static const char* newGameFile = "newGame.txt";
static const char* newLogPanelFile = "newLogPanel.txt";
static const char* newGameLogicFile = "newGameLogic.txt";

static const char* savedGameFile = "savedGame.txt";
static const char* savedLogPanelFile = "savedLogPanel.txt";
static const char* savedGameLogicFile = "savedGameLogic.txt";

int32_t initGame(struct Game* self, const struct GameCfg* cfg) {
    if (SUCCESS != initGameBoard(&self->gameBoard, cfg->gameBoardRsrcId, 
            cfg->targetRsrcId, cfg->moveSelectorRsrcId)) {
        LOGERR("Error, initGameBoard() failed");
        return FAILURE;
    }

    if (SUCCESS != initPieceHandler(&self->pieceHandler, &cfg->pieceHandlerCfg,
            self->gameLogic.activePlayerId, (void*)self, (void*)&self->gameBoard, newGameFile, newLogPanelFile)) {
        LOGERR("Error, initChessPiece() failed");
        return FAILURE;
    }

    if (SUCCESS != initPiecePromotionPanel(&self->piecePromotionPanel, 
            &cfg->piecePromotionPanelCfg, (void*)self)) {
        LOGERR("Error, initPiecePromotionPanel() failed");
        return FAILURE;
    }

    if (SUCCESS != initGameStatePanel(&self->gameStatePanel, 
            &cfg->gameStatePanelCfg, (void*)self)) {
        LOGERR("Error, initGameStatePanel() failed");
        return FAILURE;
    }

    if (SUCCESS != initGameLogic(&self->gameLogic, &cfg->gameLogicCfg, (void*)self)) {
        LOGERR("Error, initGameLogic() failed");
        return FAILURE;
    }

    self->gameExited = false;

    return SUCCESS;
}

void deinitGame(struct Game* self) {
    deinitGameBoard(&self->gameBoard);
    deinitPieceHandler(&self->pieceHandler);
    deinitPiecePromotionPanel(&self->piecePromotionPanel);
    deinitGameStatePanel(&self->gameStatePanel);
    deinitGameLogic(&self->gameLogic);
}

void handleEventGame(struct Game* self, struct InputEvent* event) {
    handleEventGameStatePanel(&self->gameStatePanel, event);
    
    if (self->piecePromotionPanel.isActive) {
        handleEventPiecePromotionPanel(&self->piecePromotionPanel, event);
        return;
    }

    handleEventPieceHandler(&self->pieceHandler, event);
}

void drawGame(struct Game* self) {
    drawGameBoard(&self->gameBoard);
    drawGameLogic(&self->gameLogic);
    drawPieceHandler(&self->pieceHandler);
    drawPiecePromotionPanel(&self->piecePromotionPanel);
    drawGameStatePanel(&self->gameStatePanel);
}

/*Proxies*/

/*Piece Handler communicate with the game 
that the turn is over*/
void finishTurnGameProxy(void* proxy) {
    //activate animator
    struct Game* self = (struct Game*)proxy;
    finishTurn(&self->gameLogic);
    invertPieces(self->pieceHandler.pieces);
    self->pieceHandler.currPlayerId = self->gameLogic.activePlayerId;
}

/*Communicate with the Panel that it should activate*/
void activatePawnPromotionGameProxy(void* proxy) {
    struct Game* self = (struct Game*)proxy;
    
    activatePiecePromotionPanel(&self->piecePromotionPanel, 
                                self->gameLogic.activePlayerId);
}

/*Communicate with the game what type of 
piece was selected on the PiecePromotionPanel*/
void onPiecePromotionSelectedGameProxy(void* proxy, PieceType pieceType) {
    struct Game* self = (struct Game*)proxy;
    promotePiecePieceHandler(&self->pieceHandler, pieceType);
}

/*Communicate with Game
to save current state of the pieces*/
int32_t onGameSavedGameProxy(void* proxy) {
    struct Game* self = (struct Game*)proxy;

    if (SUCCESS != savePieceStates(&self->pieceHandler)) {
        LOGERR("savePieceStates() failed.");
        return FAILURE;
    }

    stopGameLogic(&self->gameLogic);
    
    if(SUCCESS != saveGameLogic(&self->gameLogic)) {
        LOGERR("saveGameLogic() failed.");
        return FAILURE;
    }

    return SUCCESS;
}

int32_t onGameStartedGameProxy(void *proxy) {
    struct Game* self = (struct Game*)proxy;

    deinitPieceHandler(&self->pieceHandler);
    if (SUCCESS != initPieceHandler(&self->pieceHandler, &self->pieceHandler.cfg,
            self->gameLogic.activePlayerId, (void*)self, (void*)&self->gameBoard, newGameFile, newLogPanelFile)) {
        LOGERR("Error, initChessPiece() failed");
        return FAILURE;
    }
    
    if (SUCCESS != loadGameLogic(&self->gameLogic, newGameLogicFile)) {
        LOGERR("Error, loadGameLogic() failed");
        return FAILURE;
    }
    startGameLogic(&self->gameLogic);

    return SUCCESS;
}

int32_t onGameContinueGameProxy(void* proxy) {
    struct Game* self = (struct Game*)proxy;

    deinitPieceHandler(&self->pieceHandler);
    if (SUCCESS != initPieceHandler(&self->pieceHandler, &self->pieceHandler.cfg,
            self->gameLogic.activePlayerId, (void*)self, (void*)&self->gameBoard, savedGameFile, savedLogPanelFile)) {
        LOGERR("Error, initChessPiece() failed");
        return FAILURE;
    }

    if (SUCCESS != loadGameLogic(&self->gameLogic, savedGameLogicFile)) {
        LOGERR("Error, loadGameLogic() failed");
        return FAILURE;
    }
    startGameLogic(&self->gameLogic);

    return SUCCESS;
}


void onGameExitedGameProxy(void* proxy) {
    struct Game* self = (struct Game*)proxy;
    self->gameExited = true;
}

int32_t getNumberOfMovesGameProxy(void* proxy) {
    struct Game* self = (struct Game*)proxy;
    return self->gameLogic.numberOfMoves;
}

void increaseNumberOfMovesGameProxy(void* proxy) {
    struct Game* self = (struct Game*)proxy;
    self->gameLogic.numberOfMoves += 1;
}

int32_t onGameEndedGameProxy(void* proxy) {
    struct Game* self = (struct Game*)proxy;
    activateGameStatePanel(&self->gameStatePanel);

    return SUCCESS;
}