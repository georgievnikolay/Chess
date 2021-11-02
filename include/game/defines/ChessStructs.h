#ifndef INCLUDE_GAME_DEFINES_CHESSSTRUCTS_H_
#define INCLUDE_GAME_DEFINES_CHESSSTRUCTS_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "game/utils/BoardPos.h"

/* Forward declarations */

/*        Defines       */

struct TileData {
    struct BoardPos boardPos;
    TileType tileType;
};

#endif /* INCLUDE_GAME_DEFINES_CHESSSTRUCTS_H_ */