/*      Own include     */
#include "sdl_utils/config/TextContainerCfg.h"

/*    System includes   */
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

void insertFontConfig(struct TextContainerCfg* self, int32_t idx,
                        const struct FontConfig* fontCfg) {
    if (0 > idx || idx >= MAX_TEXT_SIZE) {
        LOGERR("Error, fontIndex: %d is out of range for font path: %s",
            idx, fontCfg->location);
        return;
    }

    if (self->isConfigOccupied[idx]) {
        LOGERR("Error, fontIndex: %d for path: %s is trying to occupy"
                "already existing path: %s",
                idx, fontCfg->location, self->fontConfigs[idx].location);
        return;
    }

    self->isConfigOccupied[idx] = true;
    self->fontConfigs[idx].fontSize = fontCfg->fontSize;
    strcpy(self->fontConfigs[idx].location, fontCfg->location);
}