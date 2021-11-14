#ifndef INCLUDE_GAME_CONFIG_GAMEBUTTONCFG_H_
#define INCLUDE_GAME_CONFIG_GAMEBUTTONCFG_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "utils/drawing/Point.h"

/* Forward declarations */

/*        Defines       */

struct GameButtonCfg {
    struct Point buttonPos;

    int32_t buttonRsrcId;
    
    int32_t buttonWidth;
    int32_t buttonHeight;
};

#endif /* INCLUDE_GAME_CONFIG_GAMEBUTTONCFG_H_ */