/*      Own include     */
#include "manager_utils/drawing/Image.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "utils/containers/Vector.h"
#include "manager_utils/managers/RsrcMgr.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

void createImage(struct Image *self, int32_t rsrcId, const struct Point *pos) {
    if (self->widget.isCreated) {
        LOGERR("Error, Image with rsrcId: %d, was already created! Will not re-create!", 
                rsrcId);
        return;        
    }

    resetWidget(&self->widget);
    
    struct DrawParams* params = &self->widget.drawParams;
    params->rsrcId = rsrcId;
    params->pos = *pos;
    self->currFrame = 0;
    self->frames = getImageFramesRsrcMgr(gRsrcMgr, params->rsrcId);
    
    self->maxFrames = getSizeVector(self->frames);
    const struct Rectangle* rect = 
            (const struct Rectangle*)getElementVector(self->frames, self->currFrame);
    params->width = rect->w;
    params->height = rect->h;
    params->widgetType = IMAGE_WIDGET;

    params->frameRect = *rect;

    self->widget.isCreated = true;
    self->widget.isDestroyed = false;
}

void destroyImage(struct Image *self) {
    if (self->widget.isDestroyed) {
        LOGERR("Error, Image with rsrcId: %d, was already destroyed!", 
                self->widget.drawParams.rsrcId);
        return;        
    }
    resetImage(self);
    self->widget.isDestroyed = true;
    self->widget.isCreated = false;
}

void resetImage(struct Image *self) {
    resetWidget(&self->widget);
}

void drawImage(struct Image* self) {
    drawWidget(&self->widget);
}

void setFrameImage(struct Image* self, int32_t frameIdx) {
    if (0 > frameIdx || frameIdx >= self->maxFrames) {
        LOGERR("Invalid frameIdx: %d requested from rsrcId: %d. Max frames: %d",
                frameIdx, self->widget.drawParams.rsrcId, self->maxFrames);
        return;
    }

    self->currFrame = frameIdx;
    const struct Rectangle* rect = 
            (const struct Rectangle*)getElementVector(self->frames, self->currFrame);
    self->widget.drawParams.frameRect = *rect;
}

void setNextFrameImage(struct Image* self) {
    ++(self->currFrame);
    const int32_t firstFrameId = 0;
    if (self->currFrame == self->maxFrames) {
        self->currFrame = firstFrameId;
    }
    const struct Rectangle* rect = 
            (const struct Rectangle*)getElementVector(self->frames, self->currFrame);
    self->widget.drawParams.frameRect = *rect;
}

void setPrevFrameImage(struct Image* self) {
    --(self->currFrame);
    const int32_t negativeIdx = - 1;
    if (self->currFrame == negativeIdx) {
        self->currFrame = self->maxFrames - 1;
    }
    const struct Rectangle* rect = 
            (const struct Rectangle*)getElementVector(self->frames, self->currFrame);
    self->widget.drawParams.frameRect = *rect;
}