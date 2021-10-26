#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_CONTAINERS_IMAGECONTAINER_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_CONTAINERS_IMAGECONTAINER_H_

/*      Own include     */

/*    System includes   */
#include "stdint.h"

/* Third party includes */

/* Own library includes */
#include "utils/containers/Vector.h"
#include "sdl_utils/config/ImageContainerCfg.h"

/* Forward declarations */
typedef struct SDL_Texture SDL_Texture;

/*        Defines       */

struct ImageContainer {
    //the textures we'll be drawing
    SDL_Texture *textures[MAX_IMAGE_SIZE];

    struct Vector textureFrames[MAX_IMAGE_SIZE]; //0, 0, imgWidth, imgHeight
};

int32_t initImageContainer(struct ImageContainer* self, 
                            const struct ImageContainerCfg* cfg);

void deinitImageContainer(struct ImageContainer* self);

SDL_Texture* getImageTextureImageContainer(
    const struct ImageContainer* self, int32_t rsrcId);

const struct Vector* getImageFramesImageContainer(
    const struct ImageContainer* self, int32_t rsrcId);

#endif /* SDL_UTILS_INCLUDE_SDL_UTILS_CONTAINERS_IMAGECONTAINER_H_ */