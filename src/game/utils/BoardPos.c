/*      Own include     */
#include "game/utils/BoardPos.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */

/* Forward declarations */

/*        Defines       */

bool areBoardPosEqual(const struct BoardPos* left, 
                      const struct BoardPos* right) {
    return (left->row == right->row) && (left->col == right->col);
}