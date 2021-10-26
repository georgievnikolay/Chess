#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_TEXTURE_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_TEXTURE_H_

/*     Own include      */

/*    System includes   */
#include <stdint.h>
 
/* Third party includes */
 
/* Own library includes */
#include "utils/drawing/DrawParams.h"
 
/* Forward declarations */
typedef struct SDL_Surface SDL_Surface;
typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct _TTF_Font TTF_Font;
struct Color;
 
/*        Defines       */

int32_t loadSurfaceFromFile(const char* filePath, SDL_Surface** outSurface);
int32_t loadTextureFromSurface(SDL_Surface** surface, SDL_Texture** outTexture);
int32_t loadTextureFromFile(const char* filePath, SDL_Texture** outTexture);
int32_t loadSurcafeFromText(const char* text, TTF_Font* font, 
                            const struct Color* color, SDL_Surface** outSurface);

int32_t loadTextureFromText(const char* text, TTF_Font* font, 
                            const struct Color* color, SDL_Texture** outTexture,
                            int32_t* outTextWidth, int32_t* outTextHeight);

void freeSurface(SDL_Surface** surface);
void freeTexture(SDL_Texture** texture);

int32_t setBlendModeTexture(SDL_Texture* texture, BlendMode blendMode);
int32_t setAlphaTexture(SDL_Texture* texture, int32_t alpha);

void setRenderer(SDL_Renderer* renderer);

#endif /* SDL_UTILS_INCLUDE_SDL_UTILS_TEXTURE_H_ */