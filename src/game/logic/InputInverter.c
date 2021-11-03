/*      Own include     */
#include "game/logic/InputInverter.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "sdl_utils/InputEvent.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

int32_t initInputInverter(struct InputInverter* self, 
                          int32_t boardWidth,
                          int32_t boardHeight) {
    self->boardWidth = boardWidth;
    self->boardHeight = boardHeight;

    return SUCCESS;
}

void invertEventInputInverter(struct InputInverter* self,
                              struct InputEvent *inputEvent) {
    switch (self->flipType) {
        case HORIZONTAL_WIDGET_FLIP:
            inputEvent->pos.y = self->boardWidth - inputEvent->pos.y;
            break;
        case VERTICAL_WIDGET_FLIP:
            inputEvent->pos.x = self->boardWidth - inputEvent->pos.x;
            break;
        case HORIZONTAL_AND_VERTICAL_WIDGET_FLIP:
            inputEvent->pos.y = self->boardWidth - inputEvent->pos.y;
            inputEvent->pos.x = self->boardWidth - inputEvent->pos.x;
            break;

        case NONE_WIDGET_FLIP:
        default:
            break;
    }
}

// void setFlipTypetInputInverter(struct InputInverter* self,
//                                WidgetFlip flipType) {

// }