#ifndef INCLUDE_GAME_ENTITIES_BOARD_GAMEBOARDANIMATOR_H_
#define INCLUDE_GAME_ENTITIES_BOARD_GAMEBOARDANIMATOR_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "utils/drawing/DrawParams.h"

/* Forward declarations */
struct Image;
/*        Defines       */

struct GameBoardAnimator {
    void *gameProxy;
    struct Image *boardImg;
    int32_t currRotation;
    WidgetFlip targetFlipType;
};

int32_t initGameBoardAnimator(struct GameBoardAnimator* self,
                              void* gameProxy, 
                              struct Image* boardImg);

void startAnimGameBoardAnimator(struct GameBoardAnimator* self, 
                                int32_t playerId);

#endif /* INCLUDE_GAME_ENTITIES_BOARD_GAMEBOARDANIMATOR_H_ */