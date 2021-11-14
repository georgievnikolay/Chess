#ifndef INCLUDE_GAME_CONFIG_GAMEPANELSCFG_H_
#define INCLUDE_GAME_CONFIG_GAMEPANELSCFG_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/config/PiecePromotionPanelCfg.h"
#include "game/config/GameStatePanelCfg.h"

/* Forward declarations */

/*        Defines       */

struct GamePanelsCfg {
    struct PiecePromotionPanelCfg piecePromotionPanelCfg;
    struct GameStatePanelCfg gameStatePanelCfg;
};

#endif /* INCLUDE_GAME_CONFIG_GAMEPANELSCFG_H_ */