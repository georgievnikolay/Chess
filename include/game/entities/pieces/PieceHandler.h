#ifndef INCLUDE_GAME_ENTITIES_PIECES_PIECEHANDLER_H_
#define INCLUDE_GAME_ENTITIES_PIECES_PIECEHANDLER_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>
#include <stdbool.h>

/* Third party includes */

/* Own library includes */
#include "game/config/PieceHandlerCfg.h"
#include "game/defines/ChessDefines.h"
#include "utils/containers/Vector.h"

/* Forward declarations */
struct InputEvent;

/*        Defines       */

struct PieceHandler {
    struct PieceHandlerCfg cfg;
    struct Vector pieces[PLAYERS_COUNT];
    void* gameBoardProxy;
    void* gameProxy;
    int32_t selectedPieceId;
    int32_t currPlayerId;
    bool isPieceGrabbed;
};

int32_t initPieceHandler(struct PieceHandler* self, 
                         const struct PieceHandlerCfg* cfg,
                         int32_t startingPlayerId,
                         void* gameProxy, void* gameBoardProxy,
                         char* fileName);

void deinitPieceHandler(struct PieceHandler* self);

void handleEventPieceHandler(struct PieceHandler* self, const struct InputEvent* event);

void drawPieceHandler(struct PieceHandler* self);

void promotePiecePieceHandler(struct PieceHandler* self, PieceType pieceType);

void invertPieces(struct Vector pieces[PLAYERS_COUNT]);

void savePieceStates(struct PieceHandler* self);

void loadPieceStates(struct PieceHandler* self);

/*TODO : MOVE THESE In some kind of helper file */
bool isOpponentKingInCheckmate(int32_t currPlayerId, struct Vector pieces[PLAYERS_COUNT]);
bool isOpponentKingInCheck(int32_t currPlayerId, struct Vector pieces[PLAYERS_COUNT]);

#endif /* INCLUDE_GAME_ENTITIES_PIECES_PIECEHANDLER_H_ */