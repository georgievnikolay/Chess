#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_DRAWMGR_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_DRAWMGR_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "sdl_utils/Renderer.h"
#include "sdl_utils/MonitorWindow.h"
#include "utils/drawing/DrawParams.h"
/* Forward declarations */
struct DrawMgrCfg;

/*        Defines       */

struct DrawMgr {
    struct Renderer renderer;

    struct MonitorWindow window;

    //Hold maximum frame rate cap
    int64_t maxFrames;
};

extern struct DrawMgr *gDrawMgr;

int32_t initDrawMgr(struct DrawMgr* self, const struct DrawMgrCfg* cfg);

void deinitDrawMgr(struct DrawMgr* self);

void clearScreenDrawMgr(struct DrawMgr* self);

void finishFrameDrawMgr(struct DrawMgr* self);

void addDrawCmdDrawMgr(struct DrawMgr* self,
                       const struct DrawParams *drawParams);

void setWidgetBlendModeDrawMgr(struct DrawMgr *self,
                               const struct DrawParams *drawParams,
                               BlendMode blendMode);

void setWidgetOpacityDrawMgr(struct DrawMgr *self,
                             const struct DrawParams *drawParams);

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_DRAWMGR_H_ */