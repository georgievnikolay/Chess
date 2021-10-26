/*     Own include      */
#include "engine/Engine.h"

/*    System includes   */
#include <stdint.h>
#include <time.h>
 
/* Third party includes */

/* Own library includes */
#include "engine/config/EngineConfig.h"
#include "manager_utils/managers/DrawMgr.h"
#include "manager_utils/managers/RsrcMgr.h"
#include "manager_utils/managers/TimerMgr.h"
#include "manager_utils/managers/ManagerHandler.h"
#include "sdl_utils/containers/TextContainer.h"
#include "utils/Log.h"
#include "utils/ErrorCodes.h"
#include "utils/time/Time.h"
#include "utils/thread/Thread.h"
 
/* Forward declarations */

/*        Defines       */

static void processEngine(struct Engine* self) {
    UNUSED(self);
    processManagerHandler();
}

static void handleEvent(struct Engine* engine) {
    handleEventDebugConsole(&engine->debugConsole, &engine->event);
    handleEventGame(&engine->game, &engine->event);
}

int32_t initEngine(struct Engine* self, const struct EngineConfig* cfg) {

    if (SUCCESS != initManagerHandler(&cfg->managerHandlerCfg)) {
        LOGERR("initManagerHandler() failed.");
        return FAILURE;
    }

    if (SUCCESS != initInputEvent(&self->event)) {
        LOGERR("initInputEvent() failed.");
        return FAILURE;
    }

    if (SUCCESS != initGame(&self->game, &cfg->gameCfg)) {
        LOGERR("initGame() failed.");
        return FAILURE;
    }

    if (SUCCESS != 
        initDebugConsole(&self->debugConsole, cfg->debugConsoleFontId)) {
        LOGERR("initDebugConsole() failed.");
        return FAILURE;
    }

    onInitEndTimerMgr(gTimerMgr);
    
    return SUCCESS;
}

void deinitEngine(struct Engine* self) {
    deinitDebugConsole(&self->debugConsole);
    deinitGame(&self->game);
    deinitInputEvent(&self->event);
    deinitManagerHandler();
}

static void mainLoop(struct Engine* self);

void startEngine(struct Engine* self) {
    mainLoop(self);
}

static void drawFrame(struct Engine* self) {
    clearScreenDrawMgr(gDrawMgr);

    drawGame(&self->game);
    drawDebugConsole(&self->debugConsole);

    finishFrameDrawMgr(gDrawMgr);
}

static bool processFrame(struct Engine* self) {
    while (pollInputEvent(&self->event)) {
        if (checkForExitRequest(&self->event)) {
            return true;
        }

        handleEvent(self);
    }

    processEngine(self);
    drawFrame(self);
    return false;
}

static void limitFPS(int64_t elapsedNanoseconds) {
    const int64_t maxNanosecodsPerFrame = SECOND_NS / gDrawMgr->maxFrames;

    const int64_t nanosecondsFpsDelay = maxNanosecodsPerFrame
        - elapsedNanoseconds;
    if (0 < nanosecondsFpsDelay) {
        thisThreadSleepFor(nanosecondsFpsDelay);
    }
}

static void mainLoop(struct Engine* self) {
    struct Time time;
    initTime(&time);

    while (true) {   
        advanceTime(&time);
        
        if (processFrame(self)) {
            return;
        }

        const int64_t elapsedTime = getElapsedNanoseconds(&time);
        struct DebugConsoleData data = { 
                .elapsedNanoseconds = elapsedTime, 
                .activeTimersCount = getActiveTimersCountTimerMgr(gTimerMgr)};
        updateDebugConsole(&self->debugConsole, &data);
        limitFPS(elapsedTime);
    }
}