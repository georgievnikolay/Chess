#ifndef INCLUDE_GAME_ENTITIES_BUTTONS_WHEELBUTTON_H_
#define INCLUDE_GAME_ENTITIES_BUTTONS_WHEELBUTTON_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "manager_utils/input/Button.h"

/* Forward declarations */
struct InputEvent;

/*        Defines       */
struct WheelButton {
    struct Button button;
    int32_t buttonId;
    void* proxy;
};

int32_t initWheelButton(struct WheelButton* wheelButton, void* proxy,
                        int32_t buttonId, int32_t rsrcId,
                        const struct Point* pos);

void deinitWheelButton(struct WheelButton* self);

void handleEventWheelButton(struct WheelButton* self, struct InputEvent* event);

void drawWheelButton(struct WheelButton* self);

#endif /* INCLUDE_GAME_ENTITIES_BUTTONS_WHEELBUTTON_H_ */