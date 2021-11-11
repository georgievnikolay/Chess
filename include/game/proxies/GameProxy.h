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

void onGameSavedGameProxy(void* proxy);

int32_t onGameStartedGameProxy(void* proxy);

int32_t onGameContinueGameProxy(void* proxy);

void onGameExitedGameProxy(void* proxy);

int32_t getNumberOfMovesGameProxy(void* proxy);

void increaseNumberOfMovesGameProxy(void* proxy);

int32_t onGameEndedGameProxy(void* proxy);

#endif /* INCLUDE_GAME_PROXIES_GAMEPROXY_H_ */