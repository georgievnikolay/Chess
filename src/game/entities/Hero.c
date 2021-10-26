/*      Own include     */
#include "game/entities/Hero.h"

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

int32_t initHero(struct Hero* self, int32_t rsrcId) {
    createImage(&self->heroImg, rsrcId, &POINT_ZERO);

    return SUCCESS;
}

void deinitHero(struct Hero* self) {
    for (int32_t i = 0; i < self->heroImg.maxFrames; i++) {
        free(getElementVector(self->heroImg.frames, i));
    }
    destroyImage(&self->heroImg);
}

void handleEventHero(struct Hero* self, struct InputEvent* event) {
    if (event->type != KEYBOARD_PRESS) {
        return;
    }

    switch (event->key) {
        case KEY_UP:
            self->heroImg.widget.drawParams.pos.y -= 10;
            break;

        case KEY_DOWN:
            self->heroImg.widget.drawParams.pos.y += 10;
            break;

        case KEY_LEFT:
            self->heroImg.widget.drawParams.pos.x -= 10;
            setPrevFrameImage(&self->heroImg);
            break;

        case KEY_RIGHT:
            self->heroImg.widget.drawParams.pos.x += 10;
            setNextFrameImage(&self->heroImg);
            break;    

        case KEY_U:
            self->heroImg.widget.drawParams.flipType = NONE_WIDGET_FLIP;
            break;

        case KEY_I:
            self->heroImg.widget.drawParams.flipType = HORIZONTAL_WIDGET_FLIP;
            break;

        case KEY_O:
            self->heroImg.widget.drawParams.flipType = VERTICAL_WIDGET_FLIP;
            break;

        case KEY_P:
            self->heroImg.widget.drawParams.flipType = 
                HORIZONTAL_AND_VERTICAL_WIDGET_FLIP;
            break;

        default:
            break;
    }    
}

void drawHero(struct Hero* self) {
    drawImage(&self->heroImg);
}