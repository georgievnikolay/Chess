#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_RSRCMGR_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_RSRCMGR_H_

/*      Own include     */
#include <stdint.h>

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "sdl_utils/containers/ImageContainer.h"
#include "sdl_utils/containers/TextContainer.h"

/* Forward declarations */
struct RsrcMgrCfg;

/*        Defines       */
struct RsrcMgr {
    struct ImageContainer imgContainer;
    struct TextContainer textContainer;
};

extern struct RsrcMgr *gRsrcMgr;

int32_t initRsrcMgr(struct RsrcMgr *self, const struct RsrcMgrCfg* cfg);

void deinitRsrcMgr(struct RsrcMgr *self);

/*ImageContainer wrapper*/
SDL_Texture* getImageTextureRsrcMgr(
    const struct RsrcMgr *self, int32_t rsrcId);

const struct Vector* getImageFramesRsrcMgr(
    const struct RsrcMgr *self, int32_t rsrcId);

/*TextContainer wrapper*/
SDL_Texture* getTextTextureRsrcMgr(
    const struct RsrcMgr* self, int32_t rsrcId);

void createTextRsrcMgr(struct RsrcMgr *self,
                             const char *text, const struct Color *color,
                             int32_t rsrcId, int32_t *outTextId,
                             int32_t *outTextWidth, int32_t *outTextHeight);

void unloadTextRsrcMgr(struct RsrcMgr *self,  int32_t textId);

void reloadTextRsrcMgr(struct RsrcMgr *self,
                             const char *text, const struct Color *color,
                             int32_t rsrcId, int32_t textId,
                             int32_t *outTextWidth, int32_t *outTextHeight);

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_RSRCMGR_H_ */