/*     Own include      */
#include "utils/time/Time.h"

/*    System includes   */
#include <string.h>
#include <errno.h>

/* Third party includes */
 
/* Own library includes */
#include "utils/ErrorCodes.h"
#include "utils/Log.h"
 
/* Forward declarations */

/*        Defines       */

void initTime(struct Time* time) {
    if (SUCCESS != clock_gettime(CLOCK_MONOTONIC, &time->startTime)) {
        LOGERR("clock_gettime() failed, reason: %s", strerror(errno))
    }

    time->elapsedLastCall.tv_sec = time->startTime.tv_sec;
    time->elapsedLastCall.tv_nsec = time->startTime.tv_nsec;
    time->elapsed.tv_sec = 0;
    time->elapsed.tv_nsec = 0;
}

void advanceTime(struct Time* time) {
    struct timespec now;

    if (SUCCESS != clock_gettime(CLOCK_MONOTONIC, &now)) {
        LOGERR("clock_gettime() failed, reason: %s", strerror(errno))
    }

    time->elapsed.tv_sec = now.tv_sec - time->elapsedLastCall.tv_sec;
    time->elapsed.tv_nsec = now.tv_nsec - time->elapsedLastCall.tv_nsec;

    time->elapsedLastCall.tv_sec = now.tv_sec;
    time->elapsedLastCall.tv_nsec = now.tv_nsec;

    if (0 > time->elapsed.tv_nsec) {
        time->elapsed.tv_nsec += SECOND_NS;
        --time->elapsed.tv_sec;
    }
}

void getElapsedTimeFromStart(struct Time* time) {
    struct timespec now;

    if (SUCCESS != clock_gettime(CLOCK_MONOTONIC, &now)) {
        LOGERR("clock_gettime() failed, reason: %s", strerror(errno));
    }

    time->elapsed.tv_sec = now.tv_sec - time->startTime.tv_sec;
    time->elapsed.tv_nsec = now.tv_nsec - time->startTime.tv_nsec;

    if (0 > time->elapsed.tv_nsec) {
        time->elapsed.tv_nsec += SECOND_NS;
        --time->elapsed.tv_sec;
    }
}

int64_t getElapsedNanoseconds(struct Time* time) {
    advanceTime(time);
    return time->elapsed.tv_sec * NANOSECOND_NS + time->elapsed.tv_nsec;
}

int64_t getElapsedMicroseconds(struct Time* time) {
    advanceTime(time);
    return time->elapsed.tv_sec * MILLISECOND_NS
        + time->elapsed.tv_nsec / MICROSECOND_NS;
}

int64_t getElapsedMilliseconds(struct Time* time) {
    advanceTime(time);
    return time->elapsed.tv_sec * MICROSECOND_NS
        + time->elapsed.tv_nsec / MILLISECOND_NS;
}

int64_t getElapsedSeconds(struct Time* time) {
    advanceTime(time);
    return time->elapsed.tv_sec;
}