#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_IMAGE_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_IMAGE_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "manager_utils/drawing/Widget.h"

/* Forward declarations */
struct Vector;

/*        Defines       */

struct Image {
    struct Widget widget;
    
    const struct Vector* frames;

    int32_t currFrame;
    int32_t maxFrames;
};

void createImage(struct Image *self, int32_t rsrcId, const struct Point *pos);

void destroyImage(struct Image *self);

void resetImage(struct Image *self);

void drawImage(struct Image* self);

void setFrameImage(struct Image* self, int32_t frameIdx);

void setNextFrameImage(struct Image* self);

void setPrevFrameImage(struct Image* self);

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_IMAGE_H_ */