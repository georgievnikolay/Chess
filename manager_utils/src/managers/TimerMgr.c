/*      Own include     */
#include "manager_utils/managers/TimerMgr.h"

/*    System includes   */
#include <stdlib.h>

/* Third party includes */

/* Own library includes */
#include "manager_utils/time/TimerClient.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

struct TimerMgr* gTimerMgr = NULL;

static void onTimerTimeout(struct TimerMgr* self, int32_t timerId, 
                           struct TimerData* timerData) {
    timerData->tcInstance->onTimeoutCb(timerData->tcInstance->clientProxy, timerId);
    if (timerData->timerType == ONESHOT_TIMER) {
        self->stoppedFrameTimers[timerId] = true;
        return;
    }

    timerData->remaining += timerData->interval;
}

static void removeTimersInternalTimerMgr(struct TimerMgr* self) {
    for (int32_t timerId = 0; timerId < MAX_SUPPORTED_TIMERS; ++timerId) {
        if (!self->stoppedFrameTimers[timerId]) {
            continue;
        }

        resetTimerData(&self->timerStorage[timerId]);
        self->stoppedFrameTimers[timerId] = false;
    }
}

int32_t initTimerMgr(struct TimerMgr* self) {
    initTime(&self->elapsedTime);

    return SUCCESS;
}

void deinitTimerMgr(struct TimerMgr* self) {
    UNUSED(self);
}

void processTimerMgr(struct TimerMgr* self) {
    const int64_t msElapsed = getElapsedMilliseconds(&self->elapsedTime);
    struct TimerData *timerData = NULL;

    for (int32_t timerId = 0; timerId < MAX_SUPPORTED_TIMERS; ++timerId) {
        timerData = &self->timerStorage[timerId];

        if (NULL == timerData->tcInstance) {
            continue;
        }

        timerData->remaining -= msElapsed;
        if (0 >= timerData->remaining) {
            onTimerTimeout(self, timerId, timerData);
        }
    }

    removeTimersInternalTimerMgr(self);
}

void startTimerTimerMgr(struct TimerMgr* self,
                        struct TimerClient* tcInstance, int64_t interval,
                        int32_t timerId, TimerType timerType) {
    if (isActiveTimerIdTimerMgr(self, timerId)) {
        LOGERR("Error, timer with Id: %d is already active! Will not start twice!", timerId);
        return;
    }

    struct TimerData* timerData = &self->timerStorage[timerId];
    timerData->tcInstance = tcInstance;
    timerData->interval = interval;
    timerData->remaining = interval;
    timerData->timerType = timerType;
}

void stopTimerTimerMgr(struct TimerMgr* self, int32_t timerId) {
    if (!isActiveTimerIdTimerMgr(self, timerId)) {
        LOGERR("Error, trying to stop non existing timer with Id: %d!", timerId);
        return;
    }
    self->stoppedFrameTimers[timerId] = true;
}

bool isActiveTimerIdTimerMgr(struct TimerMgr* self, int32_t timerId) {
    const bool isActive = (false == self->stoppedFrameTimers[timerId]) &&
                                    (NULL != self->timerStorage[timerId].tcInstance);

    return isActive;
}

void onInitEndTimerMgr(struct TimerMgr* self) {
    advanceTime(&self->elapsedTime);
}

int32_t getActiveTimersCountTimerMgr(struct TimerMgr* self) {
    int32_t count = 0;
    for (int32_t timerId = 0; timerId < MAX_SUPPORTED_TIMERS; ++timerId) {
        if (NULL == self->timerStorage[timerId].tcInstance) {
            count++;
        }
    }
    return count;
}