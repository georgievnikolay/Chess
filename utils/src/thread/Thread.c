/*     Own include      */
#include "utils/thread/Thread.h"

/*    System includes   */
#include <errno.h>

/* Third party includes */
 
/* Own library includes */
#include "utils/time/Time.h"
#include "utils/Log.h"
 
/* Forward declarations */

/*        Defines       */

void thisThreadSleepFor(int64_t sleepDurationNs) {
    if (sleepDurationNs < 0) {
        LOGERR("Error, thisThreadSleepFor() invoked with negative duration: "
            "[%ld ns]", sleepDurationNs);
    }

    struct timespec ts = { .tv_sec = sleepDurationNs / SECOND_NS,
                            .tv_nsec = sleepDurationNs % SECOND_NS };
    int32_t res = 0;
    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);
}