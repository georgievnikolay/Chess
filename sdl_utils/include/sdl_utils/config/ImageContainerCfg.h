#ifndef SDL_UTILS_INCLUDE_SDL_UTILS_CONFIG_IMAGECONTAINERCFG_H_
#define SDL_UTILS_INCLUDE_SDL_UTILS_CONFIG_IMAGECONTAINERCFG_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>
#include <stdbool.h>

/* Third party includes */

/* Own library includes */

/* Forward declarations */
#include "utils/containers/Vector.h"

/*        Defines       */
#define MAX_IMAGE_NAME_LEN 100
#define MAX_IMAGE_SIZE 50

struct ImageConfig {
    struct Vector frames;
    char location[MAX_IMAGE_NAME_LEN];
};

struct ImageContainerCfg {
    struct ImageConfig imageConfigs[MAX_IMAGE_SIZE];
    bool isConfigOccupied[MAX_IMAGE_SIZE];
};

void insertImageConfig(struct ImageContainerCfg* self, int32_t idx,
                        const struct ImageConfig* imgCfg);

#endif /* SDL_UTILS_INCLUDE_SDL_UTILS_CONFIG_IMAGECONTAINERCFG_H_ */