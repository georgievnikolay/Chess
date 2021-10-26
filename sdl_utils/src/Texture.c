/*     Own includes     */
#include "sdl_utils/Texture.h"

/*    System includes   */
#include <stdint.h>
 
/* Third party includes */
#include <SDL_image.h>
#include <SDL_ttf.h>

/* Own library includes */
#include "utils/drawing/DrawParams.h"
#include "utils/drawing/Color.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
 
/* Forward declarations */
 
/*        Defines       */

static SDL_Renderer* gRenderer = NULL;

int32_t loadSurfaceFromFile(const char* filePath, SDL_Surface** outSurface) {
    freeSurface(outSurface);

    *outSurface = IMG_Load(filePath);
    if (NULL == *outSurface) {
        LOGERR("IMG_Load() failed. Reason %s", SDL_GetError());
        return FAILURE;
    }

    return SUCCESS;
}

void freeSurface(SDL_Surface** surface) {
    if (*surface) { //sanity check
        SDL_FreeSurface(*surface);
        *surface = NULL;
    }
}

int32_t loadTextureFromSurface(SDL_Surface** surface, SDL_Texture** outTexture) {
    if (*outTexture) { ///WTF
        LOGERR("Error, texture is already populated. Memory leak prevented!");
        return FAILURE;
    }

    *outTexture = SDL_CreateTextureFromSurface(gRenderer, *surface);
    if (*outTexture == NULL) {
        LOGERR("SDL_CeateTextureFromSurface() failed. SDL Error: %s", SDL_GetError());
        return FAILURE;
    }

    freeSurface(surface);

    return SUCCESS;
}

void freeTexture(SDL_Texture** texture) {
    if (*texture) { //sanity check
        SDL_DestroyTexture(*texture);
        *texture = NULL;
    }
}

int32_t loadTextureFromFile(const char* filePath, SDL_Texture** outTexture) {
    SDL_Surface* surface = NULL;
    if (SUCCESS != loadSurfaceFromFile(filePath, &surface)) {
        LOGERR("loadSurfaceFromFile() failed for path: %s", filePath);
        return FAILURE;
    }

    if (SUCCESS != loadTextureFromSurface(&surface, outTexture)) {
        LOGERR("loadTextureFromSurface() failed for path: %s", filePath);
        return FAILURE;
    }

    return SUCCESS;
}

int32_t loadSurcafeFromText(const char* text, TTF_Font* font, 
                            const struct Color* color, SDL_Surface** outSurface) {
    
    const SDL_Color* sdlColor = (const SDL_Color*)&color->rgba;
    *outSurface = TTF_RenderText_Blended(font, text, *sdlColor);

    if (outSurface == NULL) {
        LOGERR("TTF_RenderText_Blended() failed for text %s. SDL Error: %s", 
                text, SDL_GetError());
        return FAILURE;
    }
    return SUCCESS;
}

int32_t loadTextureFromText(const char* text, TTF_Font* font, 
                            const struct Color* color, SDL_Texture** outTexture,
                            int32_t* outTextWidth, int32_t* outTextHeight) {
    SDL_Surface* textSurface = NULL;
    if (SUCCESS != loadSurcafeFromText(text, font, color, &textSurface)) {
        LOGERR("loadSurcafeFromText() failed for text %s", text);
        return FAILURE;
    }

    *outTextWidth = textSurface->w;
    *outTextHeight = textSurface->h;

    if (SUCCESS != loadTextureFromSurface(&textSurface, outTexture)) {
        LOGERR("loadTextureFromSurface() failed for text %s", text);
        return FAILURE;
    }
    
    return SUCCESS;            
}
void setRenderer(SDL_Renderer* renderer) {
    gRenderer = renderer;
}

int32_t setBlendModeTexture(SDL_Texture *texture, BlendMode blendMode) {
    if (SUCCESS != SDL_SetTextureBlendMode(texture, (SDL_BlendMode)blendMode)) {
        LOGERR("Error, SDL_SetTextureBlendMode() failed. Reason: %s", SDL_GetError());
        return FAILURE;
    }

    return SUCCESS;
}

int32_t setAlphaTexture(SDL_Texture *texture, int32_t alpha) {
    if (0 > alpha || alpha > FULL_OPACITY) {
        LOGERR("Error, invalid alpha value of %d while the accepted range is [%d-%d]", 
                alpha, ZERO_OPACITY, FULL_OPACITY);
        return FAILURE;
    }
    if (SUCCESS != SDL_SetTextureAlphaMod(texture, (uint8_t)alpha)) {
        LOGERR("Error, SDL_SetTextureAlphaMod() failed. Reason: %s", SDL_GetError());
        return FAILURE;
    }
    
    return SUCCESS;
}