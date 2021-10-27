#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_WIDGET_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_WIDGET_H_

/*      Own include     */

/*    System includes   */
#include <stdbool.h>
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "utils/drawing/DrawParams.h"

/* Forward declarations */
struct Point;

/*        Defines       */

struct Widget {
    struct DrawParams drawParams;

    bool isCreated;
    bool isDestroyed;
    bool isVisible;
    bool isAlphaModulationEnabled;
};

void drawWidget(struct Widget *self);

void resetWidget(struct Widget *self);

bool containsPointWidget(const struct Widget *self,
                         const struct Point *point);

void setOpacityWidget(struct Widget *self, int32_t opacity);

void activateAlphaModulationWidget(struct Widget *self);

void deactivateAlphaModulationWidget(struct Widget *self);

void hideWidget(struct Widget *self);

void showWidget(struct Widget *self);

void setPositionWidget(struct Widget* self, const struct Point* pos);

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_WIDGET_H_ */