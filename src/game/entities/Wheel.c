/*      Own include     */
#include "game/entities/Wheel.h"

/*    System includes   */
#include <stdlib.h>

/* Third party includes */

/* Own library includes */
#include "sdl_utils/InputEvent.h"
#include "utils/containers/Vector.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

static void processAnimation(struct Wheel* self) {
    struct DrawParams* params = &self->wheelImg.widget.drawParams;
    params->rotationAngle += 10.0;

    const double FULL_ROTATION = 360.0;
    if (params->rotationAngle >= FULL_ROTATION) {
        params->rotationAngle -= FULL_ROTATION;
    }
}

static void onTimerTimeout(void* clientProxy, int32_t timerId) {
    struct Wheel* self = (struct Wheel*)clientProxy;

    if (timerId == self->rotateWheelTimerId) {
        processAnimation(self);
    } else {
        LOGERR("Recieved unexpected timerId: %d", timerId);
    }
}

int32_t initWheel(struct Wheel* self, int32_t rsrcId, int32_t rotWheelTimerId) {
    createImage(&self->wheelImg, rsrcId, &POINT_ZERO);
    self->isAnimationStarted = false;
    self->rotateWheelTimerId = rotWheelTimerId;

    createTimer(&self->timerClient, self, onTimerTimeout);

    return SUCCESS;
}

void deinitWheel(struct Wheel* self) {
    free(getElementVector(self->wheelImg.frames, self->wheelImg.currFrame));
    destroyImage(&self->wheelImg);
}


void handleEventWheel(struct Wheel* self, struct InputEvent* event) {
    if (event->type != KEYBOARD_PRESS) {
        return;
    }

    struct DrawParams* params = &self->wheelImg.widget.drawParams;
    switch (event->key) {
        case KEY_Z:
        //put in function
            params->rotationAngle -= 10.0;
            break;

        case KEY_X:
            params->rotationAngle += 10.0;
            break;

        case KEY_C:
        //put in function
            params->rotationCenter = POINT_ZERO;
            break;

        case KEY_V:
            params->rotationCenter.x = params->width / 2;
            params->rotationCenter.y = params->height /2;
            break;

        default:
            break;
    }    
}

void drawWheel(struct Wheel* self) {
    drawImage(&self->wheelImg);
}

void startAnimationWheel(struct Wheel* self) {
    if (self->isAnimationStarted) {
        return;
    }
    startTimer(&self->timerClient, 20, self->rotateWheelTimerId, PULSE_TIMER);
    self->isAnimationStarted = true;
}

void stopAnimationWheel(struct Wheel* self) {
    if (!self->isAnimationStarted) {
        return;
    }
    
    self->isAnimationStarted = false;
    
    if (isActiveTimerId(self->rotateWheelTimerId)) {
        stopTimer(self->rotateWheelTimerId);
    }
}