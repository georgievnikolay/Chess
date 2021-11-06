/*      Own include     */

/*    System includes   */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/* Third party includes */

/* Own library includes */
#include "sdl_utils/SDLLoader.h"
#include "utils/Log.h"
#include "utils/ErrorCodes.h"
#include "engine/Engine.h"
#include "engine/EngineConfigLoader.h"

/* Forward declarations */

/*        Defines       */

static int32_t runApplication() {
    struct Engine engine;
    memset(&engine, 0, sizeof(struct Engine));

    const struct EngineConfig cfg = loadEngineConfig();

    if (SUCCESS != initEngine(&engine, &cfg)) {
        LOGERR("initEngine() failed");
        return FAILURE;
    }

    startEngine(&engine);
    deinitEngine(&engine);

    return SUCCESS;
}

int32_t main(int32_t argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);

    if (SUCCESS != SDLinit()) {
        LOGERR("SDLinit() failed.");
        return FAILURE;
    }

    if (SUCCESS != runApplication()) {
        LOGERR("runApplication() failed.");
        return FAILURE;
    }

    SDLdeinit();
    
    return SUCCESS;
} 