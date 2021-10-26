#ifndef UTILS_INCLUDE_UTILS_DRAWING_POINT_H_
#define UTILS_INCLUDE_UTILS_DRAWING_POINT_H_

/*     Own include      */
 
/*    System includes   */
#include <stdint.h>
#include <stdbool.h>

/* Third party includes */
 
/* Own library includes */
 
/* Forward declarations */
struct Rectangle;
 
/*        Defines       */

struct Point {
    int32_t x;
    int32_t y;
};

const struct Point POINT_ZERO;
const struct Point POINT_UNDEFINED;

bool pointsAreEqual(const struct Point* first, const struct Point* second);

bool isPointInsideRect(const struct Point* self, const struct Rectangle* rect);

#endif /* UTILS_INCLUDE_UTILS_DRAWING_POINT_H_ */