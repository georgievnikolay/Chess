#ifndef INCLUDE_GAME_ENTITIES_PIECES_PIECEHANDLERHELPER_H_
#define INCLUDE_GAME_ENTITIES_PIECES_PIECEHANDLERHELPER_H_

/*      Own include     */

/*    System includes   */
#include <stdbool.h>
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "manager_utils/time/TimerClient.h"
#include "manager_utils/drawing/Text.h"
#include "game/defines/ChessDefines.h"
#include "utils/containers/Vector.h"

/* Forward declarations */
struct PieceHandlerHelperCfg;

/*        Defines       */

enum KindStateDefines {
    IN_CHECK,
    IN_CHECKMATE,
    NEUTRAL,
    KING_STATES_COUNT
};

struct PieceHandlerHelper {
    struct Text kingStateTexts[KING_STATES_COUNT];
    struct TimerClient timerClient;
};

int32_t initPieceHandlerHelper(struct PieceHandlerHelper* self, 
                               const struct PieceHandlerHelperCfg* cfg);

void deinitPieceHandlerHelper(struct PieceHandlerHelper* self);

void drawPieceHandlerHelper(struct PieceHandlerHelper* self);

int32_t showOpponentKingState(struct PieceHandlerHelper* self, 
                              int32_t currPlayerId, 
                              struct Vector pieces[PLAYERS_COUNT]);

void hideOpponentKingState(struct PieceHandlerHelper* self);

#endif /* INCLUDE_GAME_ENTITIES_PIECES_PIECEHANDLERHELPER_H_ */