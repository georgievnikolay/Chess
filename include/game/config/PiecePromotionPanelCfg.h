#ifndef INCLUDE_GAME_CONFIG_PIECEPROMOTIONPANELCFG_H_
#define INCLUDE_GAME_CONFIG_PIECEPROMOTIONPANELCFG_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */

/* Forward declarations */

/*        Defines       */

struct PiecePromotionPanelCfg {
    int32_t whitePiecesRsrcId;
    int32_t blackPiecesRsrcId;
    int32_t buttonBgrRsrcId;

    int32_t gameBoardWidth;
    int32_t gameBoardHeight;

    int32_t buttonBgrWidth;
    int32_t buttonBgrHeight;

    int32_t buttonWidth;
    int32_t buttonHeight;
};

#endif /* INCLUDE_GAME_CONFIG_PIECEPROMOTIONPANELCFG_H_ */