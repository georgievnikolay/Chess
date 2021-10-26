#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_TIMEMGR_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_TIMEMGR_H_

/*      Own include     */

/*    System includes   */
#include <stdbool.h>
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "manager_utils/time/TimerData.h"
#include "utils/time/Time.h"

/* Forward declarations */
struct TimerMgrCfg;

/*        Defines       */

#define MAX_SUPPORTED_TIMERS 50

struct TimerMgr {
    struct Time elapsedTime;
    struct TimerData timerStorage[MAX_SUPPORTED_TIMERS];  //size == supportedTimersCount
    bool stoppedFrameTimers[MAX_SUPPORTED_TIMERS];        //size == supportedTimersCount
};

extern struct TimerMgr* gTimerMgr;

int32_t initTimerMgr(struct TimerMgr* self);

void deinitTimerMgr(struct TimerMgr* self);

void processTimerMgr(struct TimerMgr* self);

void startTimerTimerMgr(struct TimerMgr* self,
                        struct TimerClient *tcInstance, int64_t interval,
                        int32_t timerId, TimerType timerType);

void stopTimerTimerMgr(struct TimerMgr* self, int32_t timerId);

bool isActiveTimerIdTimerMgr(struct TimerMgr* self, int32_t timerId);

void onInitEndTimerMgr(struct TimerMgr* self);

int32_t getActiveTimersCountTimerMgr(struct TimerMgr* self);

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_TIMEMGR_H_ */