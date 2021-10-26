/*      Own include     */
#include "sdl_utils/containers/TextContainer.h"

/*    System includes   */

/* Third party includes */
#include <SDL_ttf.h>
#include <stdint.h>

/* Own library includes */
#include "sdl_utils/Texture.h"
#include "utils/drawing/Color.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

static int32_t occupyFreeSlotIndex(SDL_Texture* textures[MAX_TEXT_SIZE], 
                                SDL_Texture* textTexture, int32_t* outIdx) {
    for (int32_t i = 0; i < MAX_TEXT_SIZE; i++) {
        if (textures[i] == NULL) {
            textures[i] = textTexture;
            *outIdx = i;
            return SUCCESS;
        }
    }
    LOGERR("Error, not enough room for new text." 
        "Increase the size of the text container!");
    const int32_t invalidTextId = -1;
    *outIdx = invalidTextId;
    return FAILURE;
}

static void freeSlotIndex(SDL_Texture* textures[MAX_TEXT_SIZE], int32_t Idx) {
    freeTexture(&textures[Idx]);
}

int32_t initTextContainer(struct TextContainer* self, 
                            const struct TextContainerCfg* cfg) {

    const struct FontConfig* currFontCfg;
    for (int32_t i = 0; i < MAX_TEXT_SIZE; i++) {
        if (!cfg->isConfigOccupied[i]) {
            continue;
        }

        currFontCfg = &cfg->fontConfigs[i];

        self->fonts[i] = 
            TTF_OpenFont(currFontCfg->location, currFontCfg->fontSize);
        
        if (NULL == self->fonts[i]) {
            LOGERR("TTF_OpenFont() failed for fontPath: %s. SDL_Error: %s", 
                    currFontCfg->location, SDL_GetError());
            return FAILURE;
        }
    }

    return SUCCESS;
}

void deinitTextContainer(struct TextContainer* self) {
    for (int32_t i = 0; i < MAX_FONTS_SIZE; i++) {
        if (self->fonts[i]) {
            TTF_CloseFont(self->fonts[i]);
            self->fonts[i] = NULL;
        }
    }

    for (int32_t i = 0; i < MAX_TEXT_SIZE; i++) {
        if (self->textures[i]) {
            freeTexture(&self->textures[i]);
        }
    }
}

SDL_Texture* getTextTextureTextContainer(const struct TextContainer* self, 
                                        int32_t rsrcId) {
    if (0 > rsrcId || rsrcId >= MAX_TEXT_SIZE) {
        return NULL;
    }
    return self->textures[rsrcId];
}

void createTextTextContainer(struct TextContainer *self,
                             const char *text, const struct Color *color,
                             int32_t rsrcId, int32_t *outTextId,
                             int32_t *outTextWidth, int32_t *outTextHeight) {
    
    SDL_Texture* textTexture = NULL;

    if (SUCCESS != loadTextureFromText(text, self->fonts[rsrcId], color, 
                            &textTexture, outTextWidth, outTextHeight)) {
        LOGERR("Error, loadTextureFromText() failed for text: %s with font ID: %d",
                 text, rsrcId);
    }

    occupyFreeSlotIndex(self->textures, textTexture, outTextId);
}

void reloadTextTextContainer(struct TextContainer *self,
                             const char *text, const struct Color *color,
                             int32_t rsrcId, int32_t textId,
                             int32_t *outTextWidth, int32_t *outTextHeight) {
    freeSlotIndex(self->textures, textId);

    SDL_Texture* textTexture = NULL;    

    if (SUCCESS != loadTextureFromText(text, self->fonts[rsrcId], color, 
                            &textTexture, outTextWidth, outTextHeight)) {
        LOGERR("Error, loadTextureFromText() failed for text: %s with font ID: %d",
                 text, rsrcId);
    }

    self->textures[textId] = textTexture;
}

void unloadTextTextContainer(struct TextContainer *self,  int32_t textId) {
    freeSlotIndex(self->textures, textId);
}
