/*     Own includes     */
#include "sdl_utils/MonitorWindow.h"

/*    System includes   */
#include <stdint.h>
 
/* Third party includes */
#include <SDL_video.h>
 
/* Own library includes */
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
 
/* Forward declarations */
 
 /*        Defines       */

int32_t initMonitorWindow(struct MonitorWindow* self, const struct MonitorWindowCfg* cfg) {
    struct Point initWindowPos = cfg->windowPos;
    
    if (pointsAreEqual(&cfg->windowPos, &POINT_UNDEFINED)) {
        initWindowPos.x = SDL_WINDOWPOS_UNDEFINED;
        initWindowPos.y = SDL_WINDOWPOS_UNDEFINED;
    } else {
        initWindowPos.x = cfg->windowPos.x;
        initWindowPos.y = cfg->windowPos.y;
    }
        
    //Create window
    self->sdlWindow = SDL_CreateWindow(cfg->windowName, initWindowPos.x, 
    initWindowPos.y, cfg->width, cfg->height, cfg->mode);
    
    if (NULL == self->sdlWindow) {
        LOGERR("SDL_CreateWindow() failed. Reason %s", SDL_GetError());
        return FAILURE;
    }

    SDL_GetWindowPosition(self->sdlWindow, &self->windowRect.x, 
        &self->windowRect.y);

    return SUCCESS;
}

void deinitMonitorWindow(struct MonitorWindow* self) {
    if (self->sdlWindow) { //sanity check
        SDL_DestroyWindow(self->sdlWindow);
        self->sdlWindow = NULL;
    }
}