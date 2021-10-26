/*      Own include     */
#include "manager_utils/input/Button.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"


/* Forward declarations */

/*        Defines       */

void createButton(struct Button *self, int32_t rsrcId, const struct Point *pos) {
    createImage(&self->img, rsrcId, pos);
    self->isInputUnlocked = true;
}

void resetButton(struct Button *self) {
    resetImage(&self->img);
}

void drawButton(struct Button *self) {
drawImage(&self->img);
}

void lockInputButton(struct Button *self) {
    self->isInputUnlocked = false;
    setFrameImage(&self->img, DISABLED);
}

void unlockInputButton(struct Button *self) {
    self->isInputUnlocked = true;
    setFrameImage(&self->img, UNCLICKED);
}

bool containsEventButton(struct Button *self, const struct InputEvent *event) {
    if (!self->img.widget.isVisible) {
        return false;
    }

    const struct DrawParams* params = &self->img.widget.drawParams;
    const struct Rectangle bound = { .x = params->pos.x, .y = params->pos.y,
                                     .w = params->width, .h = params->height };

    return isPointInsideRect(&event->pos, &bound);
}