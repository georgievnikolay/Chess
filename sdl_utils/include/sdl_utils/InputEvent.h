#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_INPUTEVENT_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_INPUTEVENT_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>
 
/* Third party includes */
 
/* Own library includes */
#include "utils/drawing/Point.h"
#include "utils/input/EventDefines.h"
 
/* Forward declarations */
 typedef union SDL_Event SDL_Event;

/*        Defines       */

struct InputEvent {
    struct Point pos;       //Holds event position on the screen
    
                            // See EventDefines.h for more information
    int32_t key;
    uint8_t mouseButton;
    TouchEvent type;

    SDL_Event *sdlEvent;    // Holds the OS communication event system
};

int32_t initInputEvent(struct InputEvent* e);

void deinitInputEvent(struct InputEvent* e);

bool pollInputEvent(struct InputEvent* e);

bool checkForExitRequest(struct InputEvent* e);

#endif /* SDL_UTILS_INCLUDE_SDL_UTILS_INPUTEVENT_H_ */