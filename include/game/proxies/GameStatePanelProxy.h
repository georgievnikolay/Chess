#ifndef INCLUDE_GAME_PROXIES_GAMESTATEPANELPROXY_H_
#define INCLUDE_GAME_PROXIES_GAMESTATEPANELPROXY_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */

/* Forward declarations */

/*        Defines       */

int32_t startGameGamePanelProxy(void* proxy);

void exitGameGamePanelProxy(void* proxy);

int32_t quitGameGamePanelProxy(void* proxy);

int32_t continueGameGamePanelProxy(void* proxy);

#endif /* INCLUDE_GAME_PROXIES_GAMESTATEPANELPROXY_H_ */