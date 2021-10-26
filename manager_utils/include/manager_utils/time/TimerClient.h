#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_TIME_TIMERCLIENT_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_TIME_TIMERCLIENT_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>
#include <stdbool.h>

/* Third party includes */

/* Own library includes */
#include "manager_utils/time/TimerData.h"

/* Forward declarations */

/*        Defines       */

struct TimerClient {
    void* clientProxy;
    void (*onTimeoutCb)(void* clientProxy, int32_t timerId);
};

void createTimer(struct TimerClient* self, void* clientProxy,
                 void (*onTimeoutCb)(void* clientProxy, int32_t timerId));

void startTimer(struct TimerClient* self, int64_t interval,
                int32_t timerId, TimerType timerType);

void stopTimer(int32_t timerId);

bool isActiveTimerId(int32_t timerId);

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_TIME_TIMERCLIENT_H_ */