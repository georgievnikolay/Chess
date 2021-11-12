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

int32_t initGame(struct Game* self, const struct GameCfg* cfg) {
    if (SUCCESS != initGameLogic(&self->gameLogic, &cfg->gameLogicCfg, (void*)self)) {
        LOGERR("Error, initGameLogic() failed");
        return FAILURE;
    }

    if (SUCCESS != initGameBoard(&self->gameBoard, cfg->gameBoardRsrcId, 
            cfg->targetRsrcId, cfg->moveSelectorRsrcId)) {
        LOGERR("Error, initGameBoard() failed");
        return FAILURE;
    }

    if (SUCCESS != initPieceHandler(&self->pieceHandler, &cfg->pieceHandlerCfg, //TODO: make it const char* 
            self->gameLogic.activePlayerId, (void*)self, (void*)&self->gameBoard, "newGame.txt")) {
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
    drawPiecePromotionPanel(&self->piecePromotionPanel);
    drawPieceHandler(&self->pieceHandler);
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
    LOGC("Piece prom active for playerId: %d", 
         self->gameLogic.activePlayerId);
    
    activatePiecePromotionPanel(&self->piecePromotionPanel, 
                                self->gameLogic.activePlayerId);
}

/*Communicate with the game what type of 
piece was selected on the PiecePromotionPanel*/
void onPiecePromotionSelectedGameProxy(void* proxy, PieceType pieceType) {
    struct Game* self = (struct Game*)proxy;
    promotePiecePieceHandler(&self->pieceHandler, pieceType);

    LOGC("Recieved pieceType: %d, %d", pieceType, self->pieceHandler.selectedPieceId);
}

/*Communicate with Game
to save current state of the pieces*/
void onGameSavedGameProxy(void* proxy) {
    struct Game* self = (struct Game*)proxy;

    savePieceStates(&self->pieceHandler);

    stopGameLogic(&self->gameLogic);
    saveGameLogic(&self->gameLogic);
}

int32_t onGameStartedGameProxy(void *proxy) {
    struct Game* self = (struct Game*)proxy;

    if (SUCCESS != loadGameLogic(&self->gameLogic, "gameLogic.txt")) {
        LOGERR("Error, loadGameLogic() failed");
        return FAILURE;
    }

    deinitPieceHandler(&self->pieceHandler);
    if (SUCCESS != initPieceHandler(&self->pieceHandler, &self->pieceHandler.cfg,
            self->gameLogic.activePlayerId, (void*)self, (void*)&self->gameBoard, "newGame.txt")) {
        LOGERR("Error, initChessPiece() failed");
        return FAILURE;
    }
    startGameLogic(&self->gameLogic);

    return SUCCESS;
}

int32_t onGameContinueGameProxy(void* proxy) {
    struct Game* self = (struct Game*)proxy;

    if (SUCCESS != loadGameLogic(&self->gameLogic, "savedGameLogic.txt")) {
        LOGERR("Error, loadGameLogic() failed");
        return FAILURE;
    }
    
    deinitPieceHandler(&self->pieceHandler);
    if (SUCCESS != initPieceHandler(&self->pieceHandler, &self->pieceHandler.cfg,
            self->gameLogic.activePlayerId, (void*)self, (void*)&self->gameBoard, "savedGame.txt")) {
        LOGERR("Error, initChessPiece() failed");
        return FAILURE;
    }
    startGameLogic(&self->gameLogic);

    return SUCCESS;
}

//TODO: gameExitGameProxy to deinit game when exits -> update Debug console leaks when this is done
//TODO: find better way
void onGameExitedGameProxy(void* proxy) {
    struct Game* self = (struct Game*)proxy;
    UNUSED(self);
    
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

    // deinitPieceHandler(&self->pieceHandler);
    // if (SUCCESS != initPieceHandler(&self->pieceHandler, &self->pieceHandler.cfg,
    //         self->gameLogic.activePlayerId, (void*)self, (void*)&self->gameBoard, "newGame.txt")) {
    //     LOGERR("Error, initChessPiece() failed");
    //     return FAILURE;
    // }

    activateGameStatePanel(&self->gameStatePanel);

    return SUCCESS;
}