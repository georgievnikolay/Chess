#ifndef INCLUDE_GAME_ENTITIES_PIECES_PIECEHANDLER_H_
#define INCLUDE_GAME_ENTITIES_PIECES_PIECEHANDLER_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>
#include <stdbool.h>

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "utils/containers/Vector.h"

/* Forward declarations */
struct InputEvent;
struct PieceHandlerCfg;

/*        Defines       */

struct PieceHandler {
    struct Vector pieces[PLAYERS_COUNT];
    void* gameBoardProxy;
    int32_t selectedPieceId;
    int32_t selectedPiecePlayerId;
    bool isPieceGrabbed;
};

int32_t initPieceHandler(struct PieceHandler* self, 
                         const struct PieceHandlerCfg* cfg,
                         void* gameBoardProxy);

void deinitPieceHandler(struct PieceHandler* self);

void handleEventPieceHandler(struct PieceHandler* self, const struct InputEvent* event);

void drawPieceHandler(struct PieceHandler* self);

#endif /* INCLUDE_GAME_ENTITIES_PIECES_PIECEHANDLER_H_ */