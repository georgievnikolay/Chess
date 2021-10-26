/*      Own include     */
#include "sdl_utils/config/ImageContainerCfg.h"

/*    System includes   */
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

void insertImageConfig(struct ImageContainerCfg* self, int32_t idx,
                        const struct ImageConfig* imgCfg) {
    if (0 > idx || idx >= MAX_IMAGE_SIZE) {
        LOGERR("Error, imgIndex: %d is out of range for image path: %s",
                idx, imgCfg->location);
        return;
    }

    if (self->isConfigOccupied[idx]) {
        LOGERR("Error, imgIndex: %d for path: %s is trying to occupy"
                "already existing path: %s",
                idx, imgCfg->location, self->imageConfigs[idx].location);
        return;
    }

    self->isConfigOccupied[idx] = true;
    deepCopyVector(&imgCfg->frames, &self->imageConfigs[idx].frames);
    strcpy(self->imageConfigs[idx].location, imgCfg->location);
}