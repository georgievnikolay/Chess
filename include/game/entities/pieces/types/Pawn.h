#ifndef INCLUDE_GAME_ENTITIES_PIECES_TYPES_PAWN_H_
#define INCLUDE_GAME_ENTITIES_PIECES_TYPES_PAWN_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "utils/containers/Vector.h"

/* Forward declarations */
struct ChessPiece;

/*        Defines       */

struct Vector getMoveTilesPawn(const struct ChessPiece* piece, 
                               const struct Vector pieces[PLAYERS_COUNT]);

#endif /* INCLUDE_GAME_ENTITIES_PIECES_TYPES_PAWN_H_ */