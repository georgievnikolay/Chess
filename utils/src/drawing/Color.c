/*      Own include     */
#include "utils/drawing/Color.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */

/* Forward declarations */

/*        Defines       */
const struct Color COLOR_RED = { .rgba.r = 255, .rgba.g = 0, .rgba.b = 0, .rgba.a = 255 };
const struct Color COLOR_DARKER_RED = { .rgba.r = 128, .rgba.g = 0, .rgba.b = 0, .rgba.a = 255 };
const struct Color COLOR_GREEN = { .rgba.r = 0, .rgba.g = 255, .rgba.b = 0, .rgba.a = 255 };
const struct Color COLOR_BLUE = { .rgba.r = 0, .rgba.g = 0, .rgba.b = 255, .rgba.a = 255 };
const struct Color COLOR_BLACK = { .rgba.r = 0, .rgba.g = 0, .rgba.b = 0, .rgba.a = 255 };
const struct Color COLOR_WHITE = { .rgba.r = 255, .rgba.g = 255, .rgba.b = 255, .rgba.a = 255 };
const struct Color COLOR_GRAY = { .rgba.r = 192, .rgba.g = 192, .rgba.b = 192, .rgba.a = 255 };
const struct Color COLOR_CYAN = { .rgba.r = 0, .rgba.g = 255, .rgba.b = 255, .rgba.a = 255 };
const struct Color COLOR_MAGENTA = { .rgba.r = 255, .rgba.g = 0, .rgba.b = 255, .rgba.a = 255 };
const struct Color COLOR_YELLOW = { .rgba.r = 255, .rgba.g = 128, .rgba.b = 0, .rgba.a = 255 };
const struct Color COLOR_ORANGE = { .rgba.r = 226, .rgba.g = 106, .rgba.b = 44, .rgba.a = 255 };
const struct Color COLOR_PURPLE = { .rgba.r = 128, .rgba.g = 0, .rgba.b = 128, .rgba.a = 255 };
const struct Color COLOR_FULL_TRANSPARENT = { .rgba.r = 0, .rgba.g = 0, .rgba.b = 0, .rgba.a = 255 };

bool areColorsEqual(const struct Color* left, const struct Color* right) {
    return (left->rgba.r == right->rgba.r) &&
           (left->rgba.g == right->rgba.g) &&
           (left->rgba.b == right->rgba.b) &&
           (left->rgba.a == right->rgba.a);
}