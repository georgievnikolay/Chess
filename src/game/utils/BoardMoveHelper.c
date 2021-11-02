/*      Own include     */
#include "game/utils/BoardMoveHelper.h"

/*    System includes   */
#include <stdlib.h>

/* Third party includes */

/* Own library includes */
#include "utils/ErrorCodes.h"

/* Forward declarations */

/*        Defines       */

int32_t initBoardMoveHelper(struct BoardMoveHelper* self) {
    for (int32_t i = 0; i < DIRECTION_COUNT; i++) {
        initVector(&self->moveDirs[i], 0);
        self->isDirUsed[i] = false;
    }

    return SUCCESS;
}

void deinitBoardMoveHelper(struct BoardMoveHelper* self) {
    for (int32_t i = 0; i < DIRECTION_COUNT; i++) {
        const size_t size = getSizeVector(&self->moveDirs[i]);
        for (size_t elemId = 0; elemId < size; elemId++) {
            free(getElementVector(&self->moveDirs[i], elemId));
        }

        freeVector(&self->moveDirs[i]); 
    }
}