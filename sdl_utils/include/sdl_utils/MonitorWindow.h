#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_MONITORWINDOW_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_MONITORWINDOW_H_

/*     Own include      */

/*    System includes   */
#include <stdint.h>
 
/* Third party includes */
 
/* Own library includes */
#include "utils/drawing/Rectangle.h"
#include "sdl_utils/config/MonitorWindowCfg.h"
 
/* Forward declarations */
typedef struct SDL_Window SDL_Window;

/*        Defines       */

struct MonitorWindow {
    struct Rectangle windowRect;
    SDL_Window* sdlWindow;
};

int32_t initMonitorWindow(struct MonitorWindow* self, const struct MonitorWindowCfg* cfg);

void deinitMonitorWindow(struct MonitorWindow* self);

#endif /* SDL_UTILS_INCLUDE_SDL_UTILS_MONITORWINDOW_H_ */