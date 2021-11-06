#ifndef INCLUDE_GAME_PROXIES_GAMEPROXY_H_
#define INCLUDE_GAME_PROXIES_GAMEPROXY_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "game/defines/GameDefines.h"
#include "game/defines/ChessDefines.h"

/* Forward declarations */

/*        Defines       */

void finishTurnGameProxy(void* proxy);

void activatePawnPromotionGameProxy(void* proxy);

void onPiecePromotionSelectedGameProxy(void* proxy, PieceType pieceType);

void onGameButtonSelectedGameProxy(void* proxy, GameButtonType buttonType);

void onGameSavedGameProxy(void* proxy);

void onGameStartedGameProxy(void* proxy);

void onGameContinueGameProxy(void* proxy);

#endif /* INCLUDE_GAME_PROXIES_GAMEPROXY_H_ */