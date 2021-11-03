/*      Own include     */
#include "game/GameLogic.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "utils/ErrorCodes.h"
/* Forward declarations */

/*        Defines       */

int32_t initGameLogic(struct GameLogic* self) {
    self->activePlayerId = WHITE_PLAYER_ID;
    return SUCCESS;
}

void finishTurn(struct GameLogic* self) {
    if (self->activePlayerId == WHITE_PLAYER_ID) {
        self->activePlayerId = BLACK_PLAYER_ID;
    } else {
        self->activePlayerId = WHITE_PLAYER_ID;
    }
}