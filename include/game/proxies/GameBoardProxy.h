#ifndef INCLUDE_GAME_PROXIES_GAMEBOARDPROXY_H_
#define INCLUDE_GAME_PROXIES_GAMEBOARDPROXY_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */

/* Forward declarations */
struct BoardPos;

/*        Defines       */

void onPieceGrabbed(void* proxy, const struct BoardPos* boardPos);

void onPieceUngrabbed(void* proxy);

#endif /* INCLUDE_GAME_PROXIES_GAMEBOARDPROXY_H_ */