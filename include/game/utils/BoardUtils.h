#ifndef INCLUDE_GAME_UTILS_BOARDUTILS_H_
#define INCLUDE_GAME_UTILS_BOARDUTILS_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>
#include <stdbool.h>

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"

/* Forward declarations */
struct Point;
struct BoardPos;
struct Vector;

/*        Defines       */

struct BoardPos getBoardPos(const struct Point *absPos);

struct Point getAbsPos(const struct BoardPos *boardPos);

bool isInsideBoardBoardPos(const struct BoardPos *boardPos);

bool isInsideBoardPoint(const struct Point *absPos);

int32_t getOpponentId(int32_t activePlayerId);

struct BoardPos getAdjacentPos(Direction dir, const struct BoardPos *currPos);

bool doCollideWithPiece(const struct BoardPos *selectedPos,
                        const struct Vector *pieces,
                        int32_t *outCollisionRelativeId);

TileType getTileType(const struct BoardPos *boardPos,
                     const struct Vector *playerPieces,
                     const struct Vector *enemyPieces);


#endif /* INCLUDE_GAME_UTILS_BOARDUTILS_H_ */