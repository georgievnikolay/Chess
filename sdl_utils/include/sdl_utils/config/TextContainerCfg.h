#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_CONFIG_TEXTCONTAINERCFG_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_CONFIG_TEXTCONTAINERCFG_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>
#include <stdbool.h>

/* Third party includes */

/* Own library includes */

/* Forward declarations */

/*        Defines       */
#define MAX_FONT_NAME_LEN 50
#define MAX_TEXT_SIZE 50

struct FontConfig {
    int32_t fontSize;
    char location[MAX_FONT_NAME_LEN];
};

struct TextContainerCfg {
    struct FontConfig fontConfigs[MAX_TEXT_SIZE];
    bool isConfigOccupied[MAX_TEXT_SIZE];
};

void insertFontConfig(struct TextContainerCfg* self, int32_t idx,
                        const struct FontConfig* fontCfg);

#endif /* SDL_UTILS_INCLUDE_SDL_UTILS_CONFIG_TEXTCONTAINERCFG_H_ */