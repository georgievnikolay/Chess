#ifndef INCLUDE_GAME_CONFIG_GAMECFG_H_
#define INCLUDE_GAME_CONFIG_GAMECFG_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "game/config/PieceHandlerCfg.h"

/* Forward declarations */

/*        Defines       */

struct GameCfg {
    struct PieceHandlerCfg pieceHandlerCfg;
    int32_t gameBoardRsrcId;
    int32_t targetRsrcId;
};

#endif /* INCLUDE_GAME_CONFIG_GAMECFG_H_ */