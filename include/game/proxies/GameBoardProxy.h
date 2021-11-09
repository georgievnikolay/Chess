#ifndef INCLUDE_GAME_PROXIES_GAMEBOARDPROXY_H_
#define INCLUDE_GAME_PROXIES_GAMEBOARDPROXY_H_

/*      Own include     */

/*    System includes   */
#include <stdbool.h>

/* Third party includes */

/* Own library includes */

/* Forward declarations */
struct BoardPos;
struct Vector;

/*        Defines       */

void onPieceGrabbedGameBoardProxy(void* proxy, const struct BoardPos* boardPos,
                                  const struct Vector* moveTiles);

void onPieceUngrabbedGameBoardProxy(void* proxy);

bool isMoveAllowedGameBoardProxy(void* proxy, const struct BoardPos* boardPos);

#endif /* INCLUDE_GAME_PROXIES_GAMEBOARDPROXY_H_ */