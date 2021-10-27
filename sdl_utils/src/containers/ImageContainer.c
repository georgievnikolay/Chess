/*      Own include     */
#include "sdl_utils/containers/ImageContainer.h"

/*    System includes   */
#include "stddef.h"
#include <stdint.h>
#include <stdlib.h>

/* Third party includes */

/* Own library includes */
#include "utils/drawing/Rectangle.h"
#include "sdl_utils/Texture.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */
static struct Rectangle tempRect = {0};
static struct Vector EMPTY_VECTOR;

int32_t initImageContainer(struct ImageContainer* self, 
                            const struct ImageContainerCfg* cfg) {

    const struct ImageConfig* currImgCfg;
    for (int32_t i = 0; i < MAX_IMAGE_SIZE; i++) {
        initVector(&self->textureFrames[i], 0);

        if (!cfg->isConfigOccupied[i]) {
            continue;
        }

        currImgCfg = &cfg->imageConfigs[i];
        if (SUCCESS != loadTextureFromFile(currImgCfg->location, 
                    &(self->textures[i]))) {
            LOGERR("loadTextureFromFile() failed for filepath %s", 
                    currImgCfg->location);
            return FAILURE;
        }

        shallowCopyVector(&cfg->imageConfigs[i].frames, &self->textureFrames[i]);
    }

    /*EMPTY_VECTOR used for returning failed funtions that return Vector*/
    initVector(&EMPTY_VECTOR, 1);
    /*Since RECTANGLE_ZERO is const it cannnot be passed to pushElementVector()*/
    pushElementVector(&EMPTY_VECTOR, &tempRect);

    return SUCCESS;
}

void deinitImageContainer(struct ImageContainer* self) {
    for (int32_t i = 0; i < MAX_IMAGE_SIZE; i++) {
        if (&self->textureFrames[i]) {
            freeTexture(&self->textures[i]);
        }

        freeVector(&self->textureFrames[i]);
    }

    freeVector(&EMPTY_VECTOR);
}

SDL_Texture* getImageTextureImageContainer(const struct ImageContainer* self, 
                                            int32_t rsrcId) {
    if (0 > rsrcId || rsrcId >= MAX_IMAGE_SIZE) {
        return NULL;
    }
    return self->textures[rsrcId];
}

const struct Vector* getImageFramesImageContainer(const struct ImageContainer* self, 
                                                    int32_t rsrcId) {
    if (0 > rsrcId || rsrcId >= MAX_IMAGE_SIZE) {
        return &EMPTY_VECTOR;
    }
    return &self->textureFrames[rsrcId];
}