#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_COMMON_DEBUGCONSOLE_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_COMMON_DEBUGCONSOLE_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>
#include <stdbool.h>

/* Third party includes */

/* Own library includes */
#include "manager_utils/drawing/Text.h"

/* Forward declarations */
struct InputEvent;

/*        Defines       */
enum DebugTexts {
    MAX_FRAMES,
    ACTIVE_TIMERS,
    DEBUG_TEXTS_COUNT
};

struct DebugConsoleData {
    int64_t elapsedNanoseconds;
    int32_t activeTimersCount;
};

struct DebugConsole {
    struct Text debugTexts[DEBUG_TEXTS_COUNT];

    int32_t activeTimers;
    int64_t maxFrames;      //used to determine the current FPS
    int32_t updateCounter;  //used for skipping turns
    
    bool isActive;
};

int32_t initDebugConsole(struct DebugConsole* self, int32_t fontId);

void deinitDebugConsole(struct DebugConsole* self);

void handleEventDebugConsole(struct DebugConsole* self,
                             const struct InputEvent* event);

void updateDebugConsole(struct DebugConsole* self,
                        struct DebugConsoleData* data);

void drawDebugConsole(struct DebugConsole* self);

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_COMMON_DEBUGCONSOLE_H_ */