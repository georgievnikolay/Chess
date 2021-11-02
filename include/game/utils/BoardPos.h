#ifndef INCLUDE_GAME_UTILS_BOARDPOS_H_
#define INCLUDE_GAME_UTILS_BOARDPOS_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>
#include <stdbool.h>

/* Third party includes */

/* Own library includes */

/* Forward declarations */

/*        Defines       */

struct BoardPos {
    int32_t row;
    int32_t col;
};

bool areBoardPosEqual(const struct BoardPos* left, 
                      const struct BoardPos* right);

#endif /* INCLUDE_GAME_UTILS_BOARDPOS_H_ */