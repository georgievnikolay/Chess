/*      Own include     */
#include "game/entities/buttons/WheelButton.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "game/proxies/GameInterface.h"
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

int32_t initWheelButton(struct WheelButton *self, void *proxy,
                        int32_t buttonId, int32_t rsrcId,
                        const struct Point *pos) {
    if (proxy == NULL) {
        LOGERR("Error, NULL provided for WheelButton proxy");
        return FAILURE;
    }
    self->proxy = proxy;
    self->buttonId = buttonId;
    createButton(&self->button, rsrcId, pos);

    return SUCCESS;
}

void deinitWheelButton(struct WheelButton* self) {
    destroyImage(&self->button.img);
}

void handleEventWheelButton(struct WheelButton* self, struct InputEvent* event) {
    if (event->type == TOUCH_PRESS) {
        setFrameImage(&self->button.img, CLICKED);
    } else if (event->type == TOUCH_RELEASE) {
        setFrameImage(&self->button.img, UNCLICKED);
        onButtonPressedGameProxy(self->proxy, self->buttonId);
    }
}

void drawWheelButton(struct WheelButton* self) {
    drawButton(&self->button);
}