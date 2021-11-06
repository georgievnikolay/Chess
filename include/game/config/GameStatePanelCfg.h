#ifndef INCLUDE_GAME_CONFIG_GAMESTATEPANELCFG_H_
#define INCLUDE_GAME_CONFIG_GAMESTATEPANELCFG_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */

/* Forward declarations */

/*        Defines       */

struct GameStatePanelCfg {
    int32_t startButtonRsrcId;
    int32_t continueButtonRsrcId;
    int32_t exitButtonRsrcId;
    int32_t quitButtonRsrcId;
    int32_t startScreenRsrcId;

    int32_t gameScreenWidth;
    int32_t gameScreenHeight;

    int32_t gameBoardWidth_Height;

    int32_t buttonWidth;
    int32_t buttonHeight;
};

#endif /* INCLUDE_GAME_CONFIG_GAMESTATEPANELCFG_H_ */