#ifndef INCLUDE_GAME_ENTITIES_PIECES_PIECEHANDLERPOPULATOR_H_
#define INCLUDE_GAME_ENTITIES_PIECES_PIECEHANDLERPOPULATOR_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "utils/containers/Vector.h"
#include "game/defines/ChessDefines.h"

/* Forward declarations */

/*        Defines       */

int32_t populatePieces(struct Vector pieces[PLAYERS_COUNT], int32_t whitePiecesRsrcId, 
                       int32_t blackPiecesRsrcId, int32_t notReadyFontId);
                                  
#endif /* INCLUDE_GAME_ENTITIES_PIECES_PIECEHANDLERPOPULATOR_H_ */