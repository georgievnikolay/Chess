#ifndef INCLUDE_GAME_CONFIG_PIECEPROMOTIONBUTTONCFG_H_
#define INCLUDE_GAME_CONFIG_PIECEPROMOTIONBUTTONCFG_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "utils/drawing/Point.h"
#include "game/defines/ChessDefines.h"

/* Forward declarations */

/*        Defines       */

struct PiecePromotionButtonCfg {
    void* panelProxy;
    struct Point bgrPos;
    int32_t buttonBgrRsrcId;
    int32_t buttonWhitePieceRsrcId;
    int32_t buttonBlackPieceRsrcId;
    int32_t bgrWidth;
    int32_t bgrHeight;
    int32_t width;
    int32_t height;
    PieceType pieceType;
};


#endif /* INCLUDE_GAME_CONFIG_PIECEPROMOTIONBUTTONCFG_H_ */