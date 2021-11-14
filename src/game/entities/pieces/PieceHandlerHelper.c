/*      Own include     */
#include "game/entities/pieces/PieceHandlerHelper.h"

/*    System includes   */
#include <stdlib.h>

/* Third party includes */

/* Own library includes */
#include "common/TimerDefines.h"
#include "game/config/PieceHandlerHelperCfg.h"
#include "game/defines/ChessStructs.h"
#include "game/utils/BoardUtils.h"
#include "game/entities/board/GameBoard.h"
#include "game/entities/pieces/ChessPieceResolver.h"
#include "game/entities/pieces/types/ChessPiece.h"
#include "utils/drawing/Point.h"
#include "utils/drawing/Color.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

static void centerTextOnChessBoard(int32_t textWidth, int32_t textHeight, 
                                  int32_t boardWidth, int32_t boardHeight, 
                                  struct Point* outPoint) {
    int32_t startX = (boardWidth - textWidth) / 2 ;
    int32_t startY = (boardHeight - textHeight) / 2;

    outPoint->x = startX;
    outPoint->y = startY;
}

static void generateText(struct Text* text, const char* textContent, 
                         const struct Color* color, const  struct PieceHandlerHelperCfg* cfg) {
    struct DrawParams* params;
    
    resetText(text);
    createText(text, textContent, cfg->fontId, color, &POINT_UNDEFINED);
    params = &text->widget.drawParams;
    centerTextOnChessBoard(params->width, params->height, 
                           cfg->gameBoardWidth, cfg->gameBoardHeight, &params->pos);

    text->widget.isVisible = false;
}

/* Timer callback */
static void onTimerTimeout(void* clientProxy, int32_t timerId) {
    struct PieceHandlerHelper* self = (struct PieceHandlerHelper*)clientProxy;

    if (timerId == PIECE_HANDLER_HELPER_TIMER) {
        hideOpponentKingState(self);
    }
}

int32_t initPieceHandlerHelper(struct PieceHandlerHelper* self, 
                               const struct PieceHandlerHelperCfg* cfg) {
    
    createTimer(&self->timerClient, self, onTimerTimeout);
    generateText(&self->kingStateTexts[IN_CHECK], "CHECK", &COLOR_DARKER_RED, cfg);
    generateText(&self->kingStateTexts[IN_CHECKMATE], "CHECKMATE", &COLOR_DARKER_RED, cfg);

    return SUCCESS;
}

void deinitPieceHandlerHelper(struct PieceHandlerHelper* self) {
    for (int32_t i = 0; i < KING_STATES_COUNT; i++) {
        if (self->kingStateTexts[i].widget.isDestroyed) {
            continue;
        }
        destroyText(&self->kingStateTexts[i]);
    }
}

void drawPieceHandlerHelper(struct PieceHandlerHelper* self) {
    drawText(&self->kingStateTexts[IN_CHECK]);
    drawText(&self->kingStateTexts[IN_CHECKMATE]);
}

static bool isOpponentKingInCheck(int32_t currPlayerId, struct Vector pieces[PLAYERS_COUNT]) {
    
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
    
    /* If for some reason the opponent does not have King figure */
    if (opponentKing == NULL) {
        isInCheck = true;
        return isInCheck;
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
                
                isInCheck = true;
            }
            free(currTile);
        }
        freeVector(&currPlayerMoveTIles);
    }   

    return isInCheck;
}

static bool isOpponentKingInCheckmate(int32_t currPlayerId, struct Vector pieces[PLAYERS_COUNT]) {
    const int32_t opponentId = getOpponentId(currPlayerId);
    bool isInCheckmate = true;

    struct ChessPiece* currPiece = NULL;
    struct ChessPiece* opponentKing = NULL;

    struct Vector opponentKingMoveTiles;
    struct Vector currPieceMoveTIles;

    /* Get opponent King figure and it's moveTiles */
    size_t size = getSizeVector(&pieces[opponentId]);
    for (size_t i = 0; i < size; i++) {
        currPiece = getElementVector(&pieces[opponentId], i);
        if (currPiece->pieceType == KING) {
            opponentKing = currPiece;
            break;
        }
    }

    /* If for some reason the opponent does not have King figure */
    if (opponentKing == NULL) {
        isInCheckmate = true;
        return isInCheckmate;
    }

    struct BoardPos kingPos = opponentKing->boardPos;
    opponentKingMoveTiles = getMoveTilesPieceResolver(opponentKing, pieces);
    size_t kingMoveTilesSize = getSizeVector(&opponentKingMoveTiles);

    /* Loop through all the pieces of the current player */
    size = getSizeVector(&pieces[currPlayerId]);
    for (size_t i = 0; i < size; i++) {
        currPiece = getElementVector(&pieces[currPlayerId], i);
        
        /* Virtually remove the King from the board to get more cases covered */
        opponentKing->boardPos.col = -3;
        currPieceMoveTIles = getMoveTilesPieceResolver(currPiece, pieces);
        opponentKing->boardPos = kingPos;

        /* Loop through move tiles of the current Piece */
        size_t tilesSize = getSizeVector(&currPieceMoveTIles);
        for (size_t j = 0; j < tilesSize; j++) {
            struct TileData* currTilePiece = 
                (struct TileData*)getElementVector(&currPieceMoveTIles, j);

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
        freeVector(&currPieceMoveTIles);       
    }

    /* If the opponent King has no more MOVE_TILEs of TAKE_TILEs left it's Checkmate */  
    for (size_t i = 0; i < kingMoveTilesSize; i++) {
        struct TileData* currTileKing = 
            (struct TileData*)getElementVector(&opponentKingMoveTiles, i);

        if (currTileKing->tileType == MOVE_TILE || 
            currTileKing->tileType == TAKE_TILE) {

            isInCheckmate = false;
        }

        free(currTileKing);  
    }
    freeVector(&opponentKingMoveTiles);

    return isInCheckmate;
}

int32_t showOpponentKingState(struct PieceHandlerHelper* self, int32_t currPlayerId, struct Vector pieces[PLAYERS_COUNT]) {

    /* If King is in Check we can then check for Checkmate and if True we show text for 2,5seconds */
    if (isOpponentKingInCheck(currPlayerId, pieces)) {
        if (isOpponentKingInCheckmate(currPlayerId, pieces)) {
            showWidget(&self->kingStateTexts[IN_CHECKMATE].widget);
            startTimer(&self->timerClient, 2500, PIECE_HANDLER_HELPER_TIMER, ONESHOT_TIMER);
            return IN_CHECKMATE;
        }
        
        showWidget(&self->kingStateTexts[IN_CHECK].widget);
        startTimer(&self->timerClient, 2500, PIECE_HANDLER_HELPER_TIMER, ONESHOT_TIMER);
        return IN_CHECK;
    }

    return NEUTRAL;    
}

/* After 2,5seconds hide the texts */
void hideOpponentKingState(struct PieceHandlerHelper* self) {
    hideWidget(&self->kingStateTexts[IN_CHECKMATE].widget);
    hideWidget(&self->kingStateTexts[IN_CHECK].widget);
    stopTimer(PIECE_HANDLER_HELPER_TIMER);
}