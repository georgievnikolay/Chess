#ifndef INCLUDE_GAME_ENTITIES_BOARD_GAMEBOARD_H_
#define INCLUDE_GAME_ENTITIES_BOARD_GAMEBOARD_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "game/entities/board/MoveSelector.h"
#include "manager_utils/drawing/Image.h"
#include "utils/containers/Vector.h"

/* Forward declarations */

/*        Defines       */

struct GameBoard {
    struct MoveSelector moveSelector;
    struct Image boardImg;
    struct Image targetImg;
    struct Vector currSelectedTiles;
};

int32_t initGameBoard(struct GameBoard* self, int32_t gameBoardRsrcId, 
                      int32_t targetRsrcId, int32_t moveSelectorRsrcId);

void deinitGameBoard(struct GameBoard* self);

void drawGameBoard(struct GameBoard* self);

#endif /* INCLUDE_GAME_ENTITIES_BOARD_GAMEBOARD_H_ */