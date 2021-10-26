#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_TIME_TIMERDATA_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_TIME_TIMERDATA_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */

/* Forward declarations */
struct TimerClient;

/*        Defines       */

typedef enum {
    ONESHOT_TIMER,  //One time timer
    PULSE_TIMER,     //Repetative timer
    UNKNOWN_TIMER
} TimerType;

struct TimerData {
    int64_t interval;
    int64_t remaining;
    struct TimerClient* tcInstance;
    TimerType timerType;
};

void resetTimerData(struct TimerData* self);

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_TIME_TIMERDATA_H_ */