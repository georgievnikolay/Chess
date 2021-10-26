#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_CONFIG_MANAGERHANDLERCFG_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_CONFIG_MANAGERHANDLERCFG_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "manager_utils/managers/config/DrawMgrCfg.h"
#include "manager_utils/managers/config/RsrcMgrCfg.h"

/* Forward declarations */

/*        Defines       */

struct ManagerHandlerCfg {
    struct DrawMgrCfg drawMgrCfg;
    struct RsrcMgrCfg rscrMgrCfg;
};

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_CONFIG_MANAGERHANDLERCFG_H_ */