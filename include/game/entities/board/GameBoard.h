#ifndef INCLUDE_GAME_ENTITIES_BOARD_GAMEBOARD_H_
#define INCLUDE_GAME_ENTITIES_BOARD_GAMEBOARD_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "manager_utils/drawing/Image.h"

/* Forward declarations */

/*        Defines       */

struct GameBoard {
    struct Image boardImg;
    struct Image targetImg;
};

int32_t initGameBoard(struct GameBoard* self, int32_t gameBoardRsrcId, 
                                              int32_t targetRsrcId);

void deinitGameBoard(struct GameBoard* self);

void drawGameBoard(struct GameBoard* self);

#endif /* INCLUDE_GAME_ENTITIES_BOARD_GAMEBOARD_H_ */