/*      Own include     */
#include "manager_utils/managers/ManagerHandler.h"

/*    System includes   */
#include <stdlib.h>
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "manager_utils/managers/DrawMgr.h"
#include "manager_utils/managers/RsrcMgr.h"
#include "manager_utils/managers/TimerMgr.h"
#include "manager_utils/managers/config/ManagerHandlerCfg.h"
#include "utils/Log.h"
#include "utils/ErrorCodes.h"

/* Forward declarations */

/*        Defines       */

int32_t initManagerHandler(const struct ManagerHandlerCfg* cfg) {
    //TODO: put in function?
    gDrawMgr = (struct DrawMgr*)malloc(sizeof(struct DrawMgr));
    if (gDrawMgr == NULL) {
        LOGERR("Bad allocation for DrawMgr");
        return FAILURE;
    }
    memset(gDrawMgr, 0, sizeof(struct DrawMgr));

    if (SUCCESS != initDrawMgr(gDrawMgr, &cfg->drawMgrCfg)) {
        LOGERR("initDrawMgr() failed.");
        return FAILURE;
    }

    gRsrcMgr = (struct RsrcMgr*)malloc(sizeof(struct RsrcMgr));
    if (gRsrcMgr == NULL) {
        LOGERR("Bad allocation for gRsrcMgr");
        return FAILURE;
    }
    memset(gRsrcMgr, 0, sizeof(struct RsrcMgr));

    if (SUCCESS != initRsrcMgr(gRsrcMgr, &cfg->rscrMgrCfg)) {
        LOGERR("initRsrcMgr() failed.");
        return FAILURE;
    }

    gTimerMgr = (struct TimerMgr*)malloc(sizeof(struct TimerMgr));
    if (gTimerMgr == NULL) {
        LOGERR("Bad allocation for gTimerMgr");
        return FAILURE;
    }
    memset(gTimerMgr, 0, sizeof(struct TimerMgr));

    if (SUCCESS != initTimerMgr(gTimerMgr)) {
        LOGERR("initTimerMgr() failed.");
        return FAILURE;
    }

    return SUCCESS;
}

void deinitManagerHandler() {
    deinitRsrcMgr(gRsrcMgr);
    free(gRsrcMgr);
    gRsrcMgr = NULL;

    deinitDrawMgr(gDrawMgr);
    free(gDrawMgr);
    gDrawMgr = NULL;

    deinitTimerMgr(gTimerMgr);
    free(gTimerMgr);
    gTimerMgr = NULL;
}

void processManagerHandler() {
    //process all required managers
    processTimerMgr(gTimerMgr);
}