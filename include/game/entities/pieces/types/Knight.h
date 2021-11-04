#ifndef INCLUDE_GAME_ENTITIES_PIECES_TYPES_KNIGHT_H_
#define INCLUDE_GAME_ENTITIES_PIECES_TYPES_KNIGHT_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "utils/containers/Vector.h"

/* Forward declarations */
struct ChessPiece;

/*        Defines       */

struct Vector getMoveTilesKnight(const struct ChessPiece* self, 
                                 const struct Vector pieces[PLAYERS_COUNT]);

#endif /* INCLUDE_GAME_ENTITIES_PIECES_TYPES_KNIGHT_H_ */