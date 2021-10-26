/*     Own includes     */
#include "sdl_utils/SDLLoader.h"

/*    System includes   */
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
 
/* Third party includes */
 
/* Own library includes */
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
 
/* Forward declarations */
 
/*        Defines       */

int32_t SDLinit() {
    
    if (SUCCESS != TTF_Init()) {
        LOGERR("TTF_Init() failed: %s", SDL_GetError());
        return FAILURE;
    }

    if (SUCCESS != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        LOGERR("SDL_Init() failed: %s", SDL_GetError());
        return FAILURE;
    }
    
    const int32_t imgFlags = IMG_INIT_PNG;
    if (! (IMG_Init(imgFlags) & imgFlags)) {
        LOGERR("SDL_image could not be initialised! SDL_image Error: %s",
        IMG_GetError());
    return FAILURE;
    }

    if (0 > Mix_OpenAudio(44100, //sound frequency
            MIX_DEFAULT_FORMAT,  //sample format
            2,                   //stereo hardware channels
            2048)) {             //chunk size
        LOGERR("SDL_mixer could not be initialised! SDL Error: %s", Mix_GetError());
    return FAILURE;
  }

    return SUCCESS;
}

void SDLdeinit() {
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}