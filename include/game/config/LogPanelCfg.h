#ifndef INCLUDE_GAME_CONFIG_LOGPANELCFG_H_
#define INCLUDE_GAME_CONFIG_LOGPANELCFG_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */

/* Forward declarations */

/*        Defines       */

struct LogPanelCfg {
    int32_t fontId;

    int32_t screenWidth;
    int32_t screenHeight;

    int32_t gameBoardWidth;
    int32_t gameBoardHeight;
};

#endif /* INCLUDE_GAME_CONFIG_LOGPANELCFG_H_ */