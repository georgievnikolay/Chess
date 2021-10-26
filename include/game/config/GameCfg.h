#ifndef INCLUDE_GAME_CONFIG_GAMECFG_H_
#define INCLUDE_GAME_CONFIG_GAMECFG_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */

/* Forward declarations */

/*        Defines       */

#define MAX_IMG_NAME_LEN 50

struct GameCfg {
    int32_t heroRsrcId;
    int32_t wheelRsrcId;
    int32_t startButtonRsrcId;
    int32_t stopButtonRsrcId;
    int32_t rotWheelTimerId;
};

#endif /* INCLUDE_GAME_CONFIG_GAMECFG_H_ */