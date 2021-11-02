#ifndef INCLUDE_GAME_ENTITIES_BOARD_MOVESELECTOR_H_
#define INCLUDE_GAME_ENTITIES_BOARD_MOVESELECTOR_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>
#include <stddef.h>
/* Third party includes */

/* Own library includes */
#include "manager_utils/drawing/Image.h"

/* Forward declarations */
struct Vector;

/*        Defines       */

enum MoveSelectorDefines {
    MAX_ACTIVE_TILES = 28
};

struct MoveSelector {
    struct Image tileImgs[MAX_ACTIVE_TILES];
    size_t activeTiles;
};

int32_t initMoveSelector(struct MoveSelector* self, int32_t rsrcId);

void deinitMoveSelector(struct MoveSelector* self);

void drawMoveSelector(struct MoveSelector *self);

void markTilesMoveSelector(struct MoveSelector *self,
                           const struct Vector *markedTiles);

void unmarkTilesMoveSelector(struct MoveSelector *self);

#endif /* INCLUDE_GAME_ENTITIES_BOARD_MOVESELECTOR_H_ */