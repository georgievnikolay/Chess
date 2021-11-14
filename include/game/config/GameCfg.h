#ifndef INCLUDE_GAME_CONFIG_GAMECFG_H_
#define INCLUDE_GAME_CONFIG_GAMECFG_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "game/config/PieceHandlerCfg.h"
#include "game/config/GamePanelsCfg.h"
#include "game/config/GameLogicCfg.h"

/* Forward declarations */

/*        Defines       */

struct GameCfg {
    struct PieceHandlerCfg pieceHandlerCfg;
    struct GameLogicCfg gameLogicCfg;
    struct GamePanelsCfg gamePanelsCfg;
    
    int32_t gameBoardRsrcId;
    int32_t targetRsrcId;
    int32_t moveSelectorRsrcId;
};

#endif /* INCLUDE_GAME_CONFIG_GAMECFG_H_ */