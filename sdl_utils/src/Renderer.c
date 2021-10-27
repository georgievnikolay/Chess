/*      Own include     */
#include "sdl_utils/Renderer.h"

/*    System includes   */

/* Third party includes */
#include <SDL_render.h>
#include <SDL_hints.h>

/* Own library includes */
#include "sdl_utils/Texture.h"
#include "utils/Log.h"
#include "utils/ErrorCodes.h"
#include "utils/drawing/DrawParams.h"
#include "utils/drawing/Point.h"

/* Forward declarations */

/*        Defines       */

static int32_t drawTextureInternal(struct Renderer* self, 
                                   const struct DrawParams* drawParams, 
                                   SDL_Texture* texture) {

    const SDL_Rect destRect = {.x = drawParams->pos.x, .y = drawParams->pos.y,
                               .w = drawParams->width, .h = drawParams->height};

    const SDL_Rect* frameRect = (const SDL_Rect*)(&drawParams->frameRect);

    const SDL_Point* rotCenter = (const SDL_Point*)(&drawParams->rotationCenter);

    return SDL_RenderCopyEx(self->sdlRenderer, texture, frameRect, &destRect, 
                            drawParams->rotationAngle, rotCenter, 
                            (SDL_RendererFlip)drawParams->flipType);
}

static void drawImage(struct Renderer* self, const struct DrawParams* drawParams, 
                    SDL_Texture* texture) {

    /*If we have to change the opacity after the image is drawn 
    we change it back to FULL_OPACITY 
    so that the next image with the same texture 
    is not using the last opacity level*/
    int32_t errorCode = 0;
    if (drawParams->opacity == FULL_OPACITY) {
        errorCode = drawTextureInternal(self, drawParams, texture);
    } else {
        if (SUCCESS != setAlphaTexture(texture, drawParams->opacity)) {
            LOGERR("setAlphaTexture() failed for rsrc ID %d", drawParams->rsrcId);
        }

        errorCode = drawTextureInternal(self, drawParams, texture);

        if (SUCCESS != setAlphaTexture(texture, FULL_OPACITY)) {
            LOGERR("setAlphaTexture() failed for rsrc ID %d", drawParams->rsrcId);
        }
    }

    if (SUCCESS != errorCode){
        LOGERR("SDL_RenderCopy() failed for rsrc ID %d! SDL Error: %s", 
                drawParams->rsrcId, SDL_GetError());
    }
}

static void drawText(struct Renderer* self, const struct DrawParams* drawParams, 
                    SDL_Texture* texture) {
    drawTextureInternal(self, drawParams, texture);                    
}

int32_t initRenderer(struct Renderer* self, SDL_Window* window) {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        LOGERR("Linear texture filtering not enabled!  SDL Error: %s", SDL_GetError());
        return FAILURE;
    }

    const int32_t unspecifiedDriverID = -1;
    self->sdlRenderer = SDL_CreateRenderer(window, unspecifiedDriverID, 
                        SDL_RENDERER_ACCELERATED);
    if (self->sdlRenderer == NULL) {
        LOGERR("SDL_CreateRenderer() failed. SDL Error: %s", SDL_GetError());
        return FAILURE;
    }

    //set color to blue
    if (SUCCESS != SDL_SetRenderDrawColor(self->sdlRenderer, 192, 192, 192, SDL_ALPHA_OPAQUE)) {
        LOGERR("SDL_SetRenderDrawColor() failed. SDL Error: %s", SDL_GetError());
        return FAILURE;
    }
    
    setRenderer(self->sdlRenderer);

    return SUCCESS;
}

void deinitRenderer(struct Renderer* self) {
    if (self->sdlRenderer) {
        SDL_DestroyRenderer(self->sdlRenderer);
        self->sdlRenderer = NULL;
    }
}

void clearScreenRenderer(struct Renderer* self) {
    if (SUCCESS != SDL_RenderClear(self->sdlRenderer)) {
        LOGERR("SDL_RenderClear() failed. SDL Error: %s", SDL_GetError());
    }
}

void finishFrameRenderer(struct Renderer* self) {
    SDL_RenderPresent(self->sdlRenderer);
}

void renderTexture(struct Renderer* self, const struct DrawParams* drawParams, 
                    SDL_Texture* texture) {
    if (IMAGE_WIDGET == drawParams->widgetType) {
        drawImage(self, drawParams, texture);
    } else if (TEXT_WIDGET == drawParams->widgetType) {
        drawText(self, drawParams, texture);
    } else {
        LOGERR("Recieved invalid widgetType: %d for rsrcId %d", 
                drawParams->widgetType, drawParams->rsrcId);
    }
}