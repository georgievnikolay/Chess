/*      Own include     */
#include "manager_utils/time/TimerData.h"

/*    System includes   */
#include <stddef.h>

/* Third party includes */

/* Own library includes */

/* Forward declarations */

/*        Defines       */

void resetTimerData(struct TimerData* self) {
    self->interval = 0;
    self->remaining = 0;
    self->tcInstance = NULL;
    self->timerType = UNKNOWN_TIMER;
}