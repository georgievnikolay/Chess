/*      Own include     */
#include "manager_utils/drawing/Widget.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "manager_utils/managers/DrawMgr.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

void drawWidget(struct Widget *self) {
    if (self->isVisible) {
        addDrawCmdDrawMgr(gDrawMgr, &self->drawParams);
    }
}

void resetWidget(struct Widget *self) {
    resetDrawParams(&self->drawParams);

    self->isCreated = false;
    self->isDestroyed = false;
    self->isVisible = true;
    self->isAlphaModulationEnabled = false;
}

bool containsPointWidget(const struct Widget *self,
                         const struct Point *point) {
    const struct DrawParams* drawParams = &self->drawParams;
    const struct Rectangle rect = { .x = drawParams->pos.x, .y = drawParams->pos.y,
                                    .w = drawParams->width, .h = drawParams->height};
    return isPointInsideRect(point, &rect);
}

void setOpacityWidget(struct Widget *self, int32_t opacity) {
    if (!self->isAlphaModulationEnabled) {
        LOGERR("Error, alpha modulation was not activated for widget with rsrcId: %d!" 
                "Will not change opacity to %d", 
                self->drawParams.rsrcId, opacity);
        return;
    }
    self->drawParams.opacity = opacity;
    setWidgetOpacityDrawMgr(gDrawMgr, &self->drawParams);
}

void activateAlphaModulationWidget(struct Widget *self) {
    if (self->isAlphaModulationEnabled) {
        LOGERR("Error, alpha modulation already activated for widget with rsrcId: %d", 
                self->drawParams.rsrcId);
        return;
    }
    
    self->isAlphaModulationEnabled = true;
    setWidgetBlendModeDrawMgr(gDrawMgr, &self->drawParams, BLEND_BLEND);
}

void deactivateAlphaModulationWidget(struct Widget *self) {
    if (!self->isAlphaModulationEnabled) {
        LOGERR("Error, alpha modulation already deactivated for widget with rsrcId: %d", 
                self->drawParams.rsrcId);
        return;
    }
    
    self->isAlphaModulationEnabled = false;
    setWidgetBlendModeDrawMgr(gDrawMgr, &self->drawParams, BLEND_NONE);
}

void hideWidget(struct Widget *self) {
    self->isVisible = false;
}

void showWidget(struct Widget *self) {
    self->isVisible = true;
}