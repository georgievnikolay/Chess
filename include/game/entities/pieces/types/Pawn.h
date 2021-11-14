#ifndef INCLUDE_GAME_ENTITIES_PIECES_TYPES_PAWN_H_
#define INCLUDE_GAME_ENTITIES_PIECES_TYPES_PAWN_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "game/entities/pieces/types/ChessPiece.h"
#include "utils/containers/Vector.h"

/* Forward declarations */

/*        Defines       */

struct Pawn {
    struct ChessPiece base;
    int32_t movesCount;
    int32_t enPassantActivatedMove;
    bool isInEnPassant;
    void* gameProxy;
};

int32_t initPawn(struct Pawn* self, 
                 const struct ChessPieceCfg* cfg, 
                 void* gameProxy);

void setBoardPosPawn(struct Pawn* self, const struct BoardPos* boardPos);

struct Vector getMoveTilesPawn(const struct ChessPiece* self, 
                               struct Vector pieces[PLAYERS_COUNT]);

bool doCollideWithPiecePawn(const struct BoardPos *selectedPos,
                            const struct Vector *pieces,
                            int32_t *outCollisionRelativeId);

#endif /* INCLUDE_GAME_ENTITIES_PIECES_TYPES_PAWN_H_ */