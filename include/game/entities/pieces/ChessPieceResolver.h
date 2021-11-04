#ifndef INCLUDE_GAME_ENTITIES_PIECES_CHESSPIECERESOLVER_H_
#define INCLUDE_GAME_ENTITIES_PIECES_CHESSPIECERESOLVER_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "utils/containers/Vector.h"

/* Forward declarations */
struct ChessPiece;
struct BoardPos;
struct ChessPieceCfg;

/*        Defines       */

int32_t initChessPieceResolver(const struct ChessPieceCfg* cfg,
                               void* gameProxy,
                               struct ChessPiece** outPiece);

void setBoardPosChessPieceResolver(struct ChessPiece* piece, 
                                   const struct BoardPos* boardPos);

void deinitChessPieceResolver(struct ChessPiece* piece);

struct Vector getMoveTilesPieceResolver(struct ChessPiece* piece, 
                                        const struct Vector pieces[PLAYERS_COUNT]);

void drawChessPieceResolver(struct ChessPiece* piece);

int32_t promoteChessPiecePieceResolver(const struct ChessPieceCfg* cfg,
                                       struct ChessPiece** outPiece);

#endif /* INCLUDE_GAME_ENTITIES_PIECES_TYPES_CHESSPIECERESOLVER_H_ */