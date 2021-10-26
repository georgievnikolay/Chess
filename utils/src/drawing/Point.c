/*     Own include      */
#include "utils/drawing/Point.h"

/*    System includes   */

/* Third party includes */
 
/* Own library includes */
#include "utils/drawing/Rectangle.h"
 
/* Forward declarations */
 
/*        Defines       */

const struct Point POINT_ZERO = { .x = 0, .y = 0 };
const struct Point POINT_UNDEFINED = { .x = 10000, .y = 10000 };

bool pointsAreEqual(const struct Point* first, const struct Point* second) {
    return (first->x == second->x) && (first->y == second->y);
}

bool isPointInsideRect(const struct Point* self, const struct Rectangle* rect) {
    const bool isInsideXAxis = (rect->x <= self->x) 
            && (self->x < rect->x + rect->w);

    const bool isInsideYAxis = (rect->y <= self->y) 
            && (self->y < rect->y + rect->h);

    return isInsideXAxis && isInsideYAxis;
}