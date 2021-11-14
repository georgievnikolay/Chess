#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_MANAGERHANDLER_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_MANAGERHANDLER_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */

/* Forward declarations */
struct ManagerHandlerCfg;

/*        Defines       */

int32_t initManagerHandler(const struct ManagerHandlerCfg* cfg);

void deinitManagerHandler();

void processManagerHandler();
 
#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_MANAGERHANDLER_H_ */