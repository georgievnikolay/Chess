#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_CONTAINERS_TEXTCONTAINER_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_CONTAINERS_TEXTCONTAINER_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "sdl_utils/config/TextContainerCfg.h"

/* Forward declarations */
struct Color;
typedef struct SDL_Texture SDL_Texture;
typedef struct _TTF_Font TTF_Font;

/*        Defines       */
#define MAX_FONTS_SIZE 10
#define MAX_TEXT_SIZE 50

struct TextContainer {
    //the textures we'll be drawing
    SDL_Texture* textures[MAX_TEXT_SIZE];

    TTF_Font* fonts[MAX_FONTS_SIZE];
};

int32_t initTextContainer(struct TextContainer* self, 
                            const struct TextContainerCfg* cfg);

void deinitTextContainer(struct TextContainer* self);

SDL_Texture* getTextTextureTextContainer(
    const struct TextContainer* self, int32_t rsrcId);

void createTextTextContainer(struct TextContainer* self,
                             const char* text, const struct Color* color,
                             int32_t rsrcId, int32_t* outTextId,
                             int32_t* outTextWidth, int32_t* outTextHeight);

void unloadTextTextContainer(struct TextContainer* self,  int32_t textId);

void reloadTextTextContainer(struct TextContainer* self,
                             const char* text, const struct Color* color,
                             int32_t rsrcId, int32_t textId,
                             int32_t* outTextWidth, int32_t* outTextHeight);

#endif /* SDL_UTILS_INCLUDE_SDL_UTILS_CONTAINERS_TEXTCONTAINER_H_ */