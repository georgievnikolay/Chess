#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_CONFIG_RSRCMGRCFG_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_CONFIG_RSRCMGRCFG_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "sdl_utils/config/ImageContainerCfg.h"
#include "sdl_utils/config/TextContainerCfg.h"

/* Forward declarations */

/*        Defines       */

struct RsrcMgrCfg {
    struct ImageContainerCfg imageContainerCfg;
    struct TextContainerCfg textContainerCfg;
};

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_CONFIG_RSRCMGRCFG_H_ */