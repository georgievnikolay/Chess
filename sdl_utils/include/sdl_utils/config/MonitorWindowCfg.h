#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_CONFIG_MONITORWINDOWCFG_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_CONFIG_MONITORWINDOWCFG_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "utils/drawing/Point.h"

/* Forward declarations */

/*        Defines       */

typedef enum {
    WINDOW_SHOWN = 4,                   //SDL_WINDOW_SHOWN
    WINDOW_FULLSCREEN_DESKTOP = 4097    //SDL_WINDOW_FULLSCREEN_DESKTOP
} WindowMode;


struct MonitorWindowCfg {
    struct Point windowPos;

    const char* windowName;

    int32_t width;
    int32_t height;
    
    WindowMode mode;
};

#endif /* SDL_UTILS_INCLUDE_SDL_UTILS_CONFIG_MONITORWINDOWCFG_H_ */