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
#include "game/utils/SaveFile.h"
#include "game/entities/pieces/types/ChessPiece.h"
#include "game/entities/pieces/PieceHandlerPopulator.h"
#include "game/entities/pieces/ChessPieceResolver.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

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

static void doMovePiece(struct PieceHandler* self, 
                        struct ChessPiece* piece,
                        const struct BoardPos* selectedBoardPos) {

    increaseNumberOfMovesGameProxy(self->gameProxy);
    setBoardPosChessPieceResolver(piece, selectedBoardPos);
    const int32_t opponentId = getOpponentId(piece->playerId);
    int32_t foundIdx = -1;

    if (doCollideWithPieceChessPieceResolver(selectedBoardPos, piece, &self->pieces[opponentId], &foundIdx)) {
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
                         void* gameProxy, void* gameBoardProxy,
                         char* fileName) {
    
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
                                  cfg->blackPiecesRsrcId, gameProxy, fileName)) {
        LOGERR("Error, populatePieces() failed");
        return FAILURE;
    }

    self->isPieceGrabbed = false;
    self->selectedPieceId = 0;
    
    self->currPlayerId = startingPlayerId;
    self->cfg = *cfg;

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

    if (currPlayerId == WHITE_PLAYER_ID) {
        pieceCfg.rsrcId = self->cfg.whitePiecesRsrcId;
    } else {
        pieceCfg.rsrcId = self->cfg.blackPiecesRsrcId;
    }
    
    deinitChessPieceResolver(currPiece);
    free(currPiece);
    deleteElementVector(&self->pieces[currPlayerId], currPieceIdx);

    promoteChessPiecePieceResolver(&pieceCfg, &currPiece);

    pushElementVector(&self->pieces[currPlayerId], currPiece);
}

void savePieceStates(struct PieceHandler* self) {
    PieceType pieceTypes[TILES_IN_ROW][TILES_IN_COL];
    for (int32_t i = 0; i < TILES_IN_ROW; i++) {
        for (int32_t j = 0; j < TILES_IN_COL; j++) {
            pieceTypes[i][j] = NONE;
        }
    }

    int32_t playerIds[TILES_IN_ROW][TILES_IN_COL] = { {0} };

    for (size_t playerIdx = 0; playerIdx < PLAYERS_COUNT; playerIdx++) {
        size_t size = getSizeVector(&self->pieces[playerIdx]);
        for (size_t i = 0; i < size; i++) {
            struct ChessPiece* currPiece = 
                getElementVector(&self->pieces[playerIdx], i);
            pieceTypes[currPiece->boardPos.row][currPiece->boardPos.col] = currPiece->pieceType;
            playerIds[currPiece->boardPos.row][currPiece->boardPos.col] = currPiece->playerId;
        }
    }
    if (SUCCESS != saveFile(pieceTypes, playerIds)) {
        LOGERR("Error, failed to save the game");
    }
}



#include "game/defines/ChessStructs.h"
#include "game/entities/board/GameBoard.h"
bool isOpponentKingInCheck(int32_t currPlayerId, struct Vector pieces[PLAYERS_COUNT]) {
    
    const int32_t opponentId = getOpponentId(currPlayerId);
    bool isInCheck = false;

    struct ChessPiece* currPiece = NULL;
    struct ChessPiece* opponentKing = NULL;

    struct Vector currPlayerMoveTIles;
    
    /* Get opponent King figure */
    size_t size = getSizeVector(&pieces[opponentId]);
    for (size_t i = 0; i < size; i++) {
        currPiece = getElementVector(&pieces[opponentId], i);
        if (currPiece->pieceType == KING) {
            opponentKing = currPiece;
            break;
        }
    }
    
    /* Loop through all the pieces of the current player */
    size = getSizeVector(&pieces[currPlayerId]);
    for (size_t i = 0; i < size; i++) {
        currPiece = getElementVector(&pieces[currPlayerId], i);
        
        currPlayerMoveTIles = getMoveTilesPieceResolver(currPiece, pieces);

        /* Loop through move tiles of the current Piece */
        size_t tilesSize = getSizeVector(&currPlayerMoveTIles);
        for (size_t j = 0; j < tilesSize; j++) {
            struct TileData* currTile = 
                (struct TileData*)getElementVector(&currPlayerMoveTIles, j);
            
            /*  If TAKE_TILE of the current piece has the same position 
            *   as the opponent King then it's a Check 
            */
            if (currTile->tileType == TAKE_TILE &&
                areBoardPosEqual(&currTile->boardPos, &opponentKing->boardPos)) { 
                
                /*TODO: maybe romove it was just for testing purposes*/
                if (currPiece->playerId == WHITE_PLAYER_ID) {
                    LOGY("Black King in check from pieceType: %d", currPiece->pieceType);
                } else {
                    LOGY("White King in check from pieceType: %d", currPiece->pieceType);
                }

                isInCheck = true;
            }
            free(currTile);
        }
        freeVector(&currPlayerMoveTIles);
    }   

    return isInCheck;
}

bool isOpponentKingInCheckmate(int32_t currPlayerId, struct Vector pieces[PLAYERS_COUNT]) {
    const int32_t opponentId = getOpponentId(currPlayerId);
    bool isInCheckmate = true;

    struct ChessPiece* currPiece = NULL;
    struct ChessPiece* opponentKing = NULL;

    struct Vector opponentKingMoveTiles;
    struct Vector currPlayerMoveTIles;

    /* Get opponent King figure and it's moveTiles */
    size_t size = getSizeVector(&pieces[opponentId]);
    for (size_t i = 0; i < size; i++) {
        currPiece = getElementVector(&pieces[opponentId], i);
        if (currPiece->pieceType == KING) {
            opponentKing = currPiece;
            break;
        }
    }
    opponentKingMoveTiles = getMoveTilesPieceResolver(opponentKing, pieces);
    size_t kingMoveTilesSize = getSizeVector(&opponentKingMoveTiles);

    /* Loop through all the pieces of the current player */
    size = getSizeVector(&pieces[currPlayerId]);
    for (size_t i = 0; i < size; i++) {
        currPiece = getElementVector(&pieces[currPlayerId], i);
        
        currPlayerMoveTIles = getMoveTilesPieceResolver(currPiece, pieces);
        
        /* Loop through move tiles of the current Piece */
        size_t tilesSize = getSizeVector(&currPlayerMoveTIles);
        for (size_t j = 0; j < tilesSize; j++) {
            struct TileData* currTilePiece = 
                (struct TileData*)getElementVector(&currPlayerMoveTIles, j);

            /* For every moveTile of the current player 
            *  check all the moveTIles for the opponent King
            */
            for (size_t k = 0; k < kingMoveTilesSize; k++) {
                struct TileData* currTileKing = 
                    (struct TileData*)getElementVector(&opponentKingMoveTiles, k);
                
                /* If both moveTiles are equal we delete the one in the King's Vector */
                if (areBoardPosEqual(&currTilePiece->boardPos, &currTileKing->boardPos)) {
                    kingMoveTilesSize -= 1;
                    deleteElementVector(&opponentKingMoveTiles, k);
                    free(currTileKing);
                }
            }
            free(currTilePiece);
        } 
        freeVector(&currPlayerMoveTIles);       
    }

    /* If the opponent King has no more MOVE_TILEs left it's Checkmate */
    for (size_t i = 0; i < kingMoveTilesSize; i++) {
        struct TileData* currTileKing = 
            (struct TileData*)getElementVector(&opponentKingMoveTiles, i);

        if (currTileKing->tileType == MOVE_TILE) {
            isInCheckmate = false;
        }  
        free(currTileKing);  
    }
    freeVector(&opponentKingMoveTiles);

    if (isInCheckmate) {
        /*TODO: maybe romove it was just for testing purposes*/
        if (currPiece->playerId == WHITE_PLAYER_ID) {
            LOGY("Black King in checkmate");
        } else {
            LOGY("White King in checkmate");
        }
    }

    return isInCheckmate;
}