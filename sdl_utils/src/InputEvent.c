/*     Own include      */
#include "sdl_utils/InputEvent.h"

/*    System includes   */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
 
/* Third party includes */
#include <SDL_events.h>
 
/* Own library includes */
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
 
/* Forward declarations */
 
/*        Defines       */

static void setEventTypeInternal(struct InputEvent *e) {

    SDL_Event* event = e->sdlEvent;

    switch (e->sdlEvent->type) {
        case KEYBOARD_PRESS_TYPE:
            e->key = event->key.keysym.sym;
            e->mouseButton = MOUSE_UNKNOWN;
            e->type = KEYBOARD_PRESS;
            break;

        case KEYBOARD_RELEASE_TYPE:
            e->key = event->key.keysym.sym;
            e->mouseButton = MOUSE_UNKNOWN;
            e->type = KEYBOARD_RELEASE;
            break;

        case MOUSE_PRESS_TYPE:
            e->key = KEY_UNKNOWN;
            e->mouseButton = event->button.button;
            e->type = TOUCH_PRESS;
            break;
            
        case FINGER_PRESS_TYPE:
            e->key = KEY_UNKNOWN;
            e->mouseButton = MOUSE_UNKNOWN;
            e->type = TOUCH_PRESS;
            break;

        case MOUSE_RELEASE_TYPE:
            e->key = KEY_UNKNOWN;
            e->mouseButton = event->button.button;
            e->type = TOUCH_RELEASE;
            break;

        case FINGER_RELEASE_TYPE:
            e->key = KEY_UNKNOWN;
            e->mouseButton = MOUSE_UNKNOWN;
            e->type = TOUCH_RELEASE;
            break;

        //X is pressed on the window (or CTRL-C signal is sent)
        case QUIT_TYPE:
        case WINDOW_TYPE:
        case TEXTEDITTING:
        case MOUSE_MOTION:
        case AUDIO_DEVICE_ADDED:
        case TEXT_INPUT_TYPE:
        case MOUSE_WHEEL_MOTION:
            e->key = KEY_UNKNOWN;
            e->mouseButton = MOUSE_UNKNOWN;
            e->type = TOUCH_EVENT_UNKNOWN;
            break;

        default:
        LOGERR("Error, recieved unsupported eventType: %d", e->sdlEvent->type);
            break;
    }
}

int32_t initInputEvent(struct InputEvent* e) {
    e->pos = POINT_UNDEFINED;
    e->key = KEY_UNKNOWN;
    e->mouseButton = MOUSE_UNKNOWN;
    e->type = TOUCH_EVENT_UNKNOWN;

    e->sdlEvent = (SDL_Event*)malloc(sizeof(SDL_Event));
    if (NULL == e->sdlEvent) {
        LOGERR("Error, bad alloc for SDL_Event");
        return FAILURE;
    }

    memset(e->sdlEvent, 0, sizeof(SDL_Event));

    return SUCCESS;
}

void deinitInputEvent(struct InputEvent* e) {
    if (e->sdlEvent != NULL) {
        free(e->sdlEvent);
        e->sdlEvent = NULL;
    }
}

bool pollInputEvent(struct InputEvent* e) {
    if (0 == SDL_PollEvent(e->sdlEvent)) {
        return false;
    }

    SDL_GetMouseState(&e->pos.x, &e->pos.y);
    setEventTypeInternal(e);

    return true;
}

bool checkForExitRequest(struct InputEvent* e) {
    return (e->sdlEvent->type == QUIT_TYPE) 
        || (e->type == KEYBOARD_PRESS && KEY_ESCAPE == e->key);
}