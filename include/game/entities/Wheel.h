#ifndef INCLUDE_GAME_ENTITIES_WHEEL_H_
#define INCLUDE_GAME_ENTITIES_WHEEL_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "manager_utils/drawing/Image.h"
#include "manager_utils/time/TimerClient.h"

/* Forward declarations */
struct InputEvent;

/*        Defines       */
struct Wheel {
    struct TimerClient timerClient;
    struct Image wheelImg;
    int32_t rotateWheelTimerId;
    bool isAnimationStarted;
};

int32_t initWheel(struct Wheel* self, int32_t rsrcId, int32_t rotWheelTimerId);

void deinitWheel(struct Wheel* self);

void handleEventWheel(struct Wheel* self, struct InputEvent* event);

void drawWheel(struct Wheel* self);

void startAnimationWheel(struct Wheel* self);

void stopAnimationWheel(struct Wheel* self);

#endif /* INCLUDE_GAME_ENTITIES_WHEEL_H_ */