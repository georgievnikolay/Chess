#ifndef INCLUDE_GAME_UTILS_BOARDMOVEHELPER_H_
#define INCLUDE_GAME_UTILS_BOARDMOVEHELPER_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>
#include <stdbool.h>

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "utils/containers/Vector.h"

/* Forward declarations */

/*        Defines       */

struct BoardMoveHelper {
    struct Vector moveDirs[DIRECTION_COUNT];
    bool isDirUsed[DIRECTION_COUNT];
};

int32_t initBoardMoveHelper(struct BoardMoveHelper* self);

void deinitBoardMoveHelper(struct BoardMoveHelper* self);

#endif /* INCLUDE_GAME_UTILS_BOARDMOVEHELPER_H_ */