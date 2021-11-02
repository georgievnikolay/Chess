#ifndef INCLUDE_GAME_ENTITIES_PIECES_TYPES_UNFINISHEDPIECE_H_
#define INCLUDE_GAME_ENTITIES_PIECES_TYPES_UNFINISHEDPIECE_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "game/entities/pieces/types/ChessPiece.h"
#include "manager_utils/drawing/Text.h"
#include "utils/containers/Vector.h"

/* Forward declarations */

/*        Defines       */

struct UnfinishedPiece {
    struct ChessPiece base;
    struct Text notReadyText;
};

int32_t initUnfinishedPiece(struct UnfinishedPiece* self, 
                            const struct ChessPieceCfg* cfg, int32_t fontId);

void deinitUnfinishedPiece(struct UnfinishedPiece* self);

void drawUnfinishedPiece(struct UnfinishedPiece* self);

void setBoardPosUnfinishedPiece(struct UnfinishedPiece* self,
                                const struct BoardPos* boardPos);

struct Vector getMoveTilesUnfinishedPiece(
    struct UnfinishedPiece* self, const struct Vector pieces[PLAYERS_COUNT]);

#endif /* INCLUDE_GAME_ENTITIES_PIECES_TYPES_UNFINISHEDPIECE_H_ */