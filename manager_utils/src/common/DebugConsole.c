/*      Own include     */
#include "manager_utils/common/DebugConsole.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "manager_utils/managers/DrawMgr.h"
#include "utils/time/Time.h"
#include "sdl_utils/InputEvent.h"
#include "utils/drawing/Color.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

static void updateFPSText(struct Text* text, int64_t value) {
    char textContent[50];
    snprintf(textContent, 50, "FPS: %ld", value);
    setText(text, textContent);
}

static void updateActiveTimersText(struct Text* text, int64_t value) {
    char textContent[50];
    snprintf(textContent, 50, "Active Timers: %ld", value);
    setText(text, textContent);
}

#define SKIP_STEPS 30

int32_t initDebugConsole(struct DebugConsole* self, int32_t fontId) {
    struct Point textPos = { .x = 20, .y = 20 };
    createText(&self->debugTexts[MAX_FRAMES], "0", fontId, &COLOR_YELLOW, &textPos);

    textPos.y += 30;
    createText(&self->debugTexts[ACTIVE_TIMERS], "0", fontId, &COLOR_YELLOW, &textPos);

    self->isActive = false;

    self->updateCounter = SKIP_STEPS;

    return SUCCESS;
}

void deinitDebugConsole(struct DebugConsole* self) {
    for (int32_t i = 0; i < DEBUG_TEXTS_COUNT; i++) {
        destroyText(&self->debugTexts[i]);
    }
}

void handleEventDebugConsole(struct DebugConsole* self,
                             const struct InputEvent* event) {
    if (event->type != KEYBOARD_PRESS) {
        return;
    }

    if (event->key == KEY_TILDA) {
        self->isActive = !self->isActive;
    }
}

void updateDebugConsole(struct DebugConsole* self,
                        struct DebugConsoleData* data) {

    self->updateCounter--;
    if (0 < self->updateCounter) {
        return;
    }
    self->updateCounter = SKIP_STEPS;

    self->activeTimers = data->activeTimersCount;

    self->maxFrames = SECOND_NS / data->elapsedNanoseconds;
    if (self->maxFrames > gDrawMgr->maxFrames) {
        self->maxFrames = gDrawMgr->maxFrames;
    }
    updateFPSText(&self->debugTexts[MAX_FRAMES], self->maxFrames);
    updateActiveTimersText(&self->debugTexts[ACTIVE_TIMERS], self->activeTimers);
}

void drawDebugConsole(struct DebugConsole* self) {
    if (self->isActive) {
        for (int32_t i = 0; i < DEBUG_TEXTS_COUNT; i++) {
            drawText(&self->debugTexts[i]);
        }
    }
}
