#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_CONFIG_DRAWMGRCFG_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_CONFIG_DRAWMGRCFG_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "sdl_utils/config/MonitorWindowCfg.h"

/* Forward declarations */

/*        Defines       */

struct DrawMgrCfg {
    struct MonitorWindowCfg windowCfg;
    int64_t maxFrames;
};

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_CONFIG_DRAWMGRCFG_H_ */