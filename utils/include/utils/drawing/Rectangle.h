#ifndef UTILS_INCLUDE_UTILS_DRAWING_RECTANGLE_H_
#define UTILS_INCLUDE_UTILS_DRAWING_RECTANGLE_H_

/*     Own includes     */

/*    System includes   */
#include <stdint.h>
#include <stdbool.h>

/* Third party includes */
 
/* Own library includes */
 
/* Forward declarations */
 
/*        Defines       */

struct Rectangle {
    int32_t x;
    int32_t y;
    int32_t w;
    int32_t h;
};

const struct Rectangle RECTANGLE_ZERO;
const struct Rectangle RECTANGLE_UNDEFINED;

#endif /* UTILS_INCLUDE_UTILS_DRAWING_RECTANGLE_H_ */