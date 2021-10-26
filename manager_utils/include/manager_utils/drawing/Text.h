#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_TEXT_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_TEXT_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "manager_utils/drawing/Widget.h"
#include "utils/drawing/Color.h"

/* Forward declarations */

/*        Defines       */

struct Text {
    struct Widget widget;
    char *textContent;
    struct Color color;
    int32_t fontId;
};

void createText(struct Text *self, const char *textContent, int32_t fontId,
                const struct Color *color, const struct Point *pos);

void destroyText(struct Text *self);

void resetText(struct Text *self);

void setText(struct Text *self, const char *textContent);

void setColorText(struct Text *self, const struct Color *color);

void drawText(struct Text *self);

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_TEXT_H_ */