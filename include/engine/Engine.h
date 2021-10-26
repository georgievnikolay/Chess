#ifndef INCLUDE_ENGINE_ENGINE_H_
#define INCLUDE_ENGINE_ENGINE_H_

/*     Own includes     */

/*    System includes   */
 
/* Third party includes */
 
/* Own library includes */
#include "manager_utils/common/DebugConsole.h"
#include "sdl_utils/InputEvent.h"
#include "game/Game.h"
 
/* Forward declarations */
typedef struct EngineConfig EngineConfig;

/*        Defines       */

struct Engine {
    struct InputEvent event;
    struct Game game;
    struct DebugConsole debugConsole;
};

int32_t initEngine(struct Engine* self, const struct EngineConfig* cfg);

void deinitEngine(struct Engine* self);

void startEngine(struct Engine* self);

#endif /* INCLUDE_ENGINE_ENGINE_H_ */