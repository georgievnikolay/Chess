#ifndef INCLUDE_GAME_UTILS_BOARDUTILS_H_
#define INCLUDE_GAME_UTILS_BOARDUTILS_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>
#include <stdbool.h>

/* Third party includes */

/* Own library includes */

/* Forward declarations */
struct Point;
struct BoardPos;

/*        Defines       */

struct BoardPos getBoardPos(const struct Point *absPos);

struct Point getAbsPos(const struct BoardPos *boardPos);

bool isInsideBoardBoardPos(const struct BoardPos *boardPos);

bool isInsideBoardPoint(const struct Point *absPos);

#endif /* INCLUDE_GAME_UTILS_BOARDUTILS_H_ */