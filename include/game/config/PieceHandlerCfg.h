#ifndef INCLUDE_GAME_CONFIG_PIECEHANDLERCFG_H_
#define INCLUDE_GAME_CONFIG_PIECEHANDLERCFG_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "game/config/PieceHandlerHelperCfg.h"

/* Forward declarations */

/*        Defines       */

struct PieceHandlerCfg {
    struct PieceHandlerHelperCfg pieceHandlerHelperCfg;
    int32_t whitePiecesRsrcId;
    int32_t blackPiecesRsrcId;
};

#endif /* INCLUDE_GAME_CONFIG_PIECEHANDLERCFG_H_ */