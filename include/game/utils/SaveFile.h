#ifndef INCLUDE_GAME_UTILS_SAVEFILE_H_
#define INCLUDE_GAME_UTILS_SAVEFILE_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"

/* Forward declarations */

/*        Defines       */

int32_t loadFile(PieceType outPieces[TILES_IN_ROW][TILES_IN_COL],
                 int32_t playerIds[TILES_IN_ROW][TILES_IN_COL]);

int32_t saveFile(const PieceType allPieces[TILES_IN_ROW][TILES_IN_COL],
                 int32_t playerIds[TILES_IN_ROW][TILES_IN_COL]);

#endif /* INCLUDE_GAME_UTILS_SAVEFILE_H_ */