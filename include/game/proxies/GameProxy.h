#ifndef INCLUDE_GAME_PROXIES_GAMEPROXY_H_
#define INCLUDE_GAME_PROXIES_GAMEPROXY_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"

/* Forward declarations */

/*        Defines       */

void finishTurnGameProxy(void* proxy);

void activatePawnPromotionGameProxy(void* proxy);

void onPiecePromotionSelectedGameProxy(void* proxy, PieceType pieceType);

#endif /* INCLUDE_GAME_PROXIES_GAMEPROXY_H_ */