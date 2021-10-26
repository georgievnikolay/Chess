#ifndef INCLUDE_ENGINE_CONFIG_ENGINECONFIG_H_
#define INCLUDE_ENGINE_CONFIG_ENGINECONFIG_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "manager_utils/managers/config/ManagerHandlerCfg.h"
#include "game/config/GameCfg.h"

/* Forward declarations */

/*        Defines       */

struct EngineConfig {
    struct ManagerHandlerCfg managerHandlerCfg;
    struct GameCfg gameCfg;
    int32_t debugConsoleFontId;
};

#endif /* INCLUDE_ENGINE_CONFIG_ENGINECONFIG_H_ */