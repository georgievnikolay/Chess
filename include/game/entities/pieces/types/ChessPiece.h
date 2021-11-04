#ifndef INCLUDE_GAME_ENTITIES_PIECES_TYPES_CHESSPIECE_H_
#define INCLUDE_GAME_ENTITIES_PIECES_TYPES_CHESSPIECE_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "manager_utils/drawing/Image.h"
#include "game/defines/ChessDefines.h"
#include "game/utils/BoardPos.h"

/* Forward declarations */
struct InputEvent;

/*        Defines       */

struct ChessPieceCfg {
    int32_t rsrcId;
    struct BoardPos boardPos;
    int32_t playerId;
    PieceType pieceType;
};

struct ChessPiece {
    struct Image pieceImg;
    struct BoardPos boardPos;
    int32_t playerId;
    PieceType pieceType;
};

int32_t initChessPiece(struct ChessPiece* self, const struct ChessPieceCfg* cfg);

void deinitChessPiece(struct ChessPiece* self);

void drawChessPiece(struct ChessPiece* self);

bool containsEventChessPiece(struct ChessPiece* self,
                             const struct InputEvent* event);

void setBoardPosChessPiece(struct ChessPiece* self,
                           const struct BoardPos* boardPos);

#endif /* INCLUDE_GAME_ENTITIES_PIECES_TYPES_CHESSPIECE_H_ */