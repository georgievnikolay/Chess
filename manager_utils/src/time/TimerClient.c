/*      Own include     */
#include "manager_utils/time/TimerClient.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "manager_utils/managers/TimerMgr.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

void createTimer(struct TimerClient* self, void* clientProxy,
                 void (*onTimeoutCb)(void* clientProxy, int32_t timerId)) {
    self->clientProxy = clientProxy;
    self->onTimeoutCb = onTimeoutCb;
}

void startTimer(struct TimerClient* self, int64_t interval,
                int32_t timerId, TimerType timerType) {
    const int64_t minInterval = 20;
    if (interval < minInterval) {
        LOGERR("Invalid requested timer interval: %ld for timerId: %d" 
               " while minimal timerInterval is: %ld", interval, timerId, minInterval);
        return;
    }
    startTimerTimerMgr(gTimerMgr, self, interval, timerId, timerType);
}

void stopTimer(int32_t timerId) {
    stopTimerTimerMgr(gTimerMgr, timerId);
}

bool isActiveTimerId(int32_t timerId) {
    return isActiveTimerIdTimerMgr(gTimerMgr, timerId);
}