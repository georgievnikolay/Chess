/*      Own include     */
#include "manager_utils/managers/RsrcMgr.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "manager_utils/managers/config/RsrcMgrCfg.h"
#include "utils/Log.h"
#include "utils/ErrorCodes.h"

/* Forward declarations */

/*        Defines       */

struct RsrcMgr* gRsrcMgr = NULL;

int32_t initRsrcMgr(struct RsrcMgr* self, const struct RsrcMgrCfg* cfg) {
    if (self == NULL) {
        LOGERR("Error NULL provided for gRsrcMgr");
        return FAILURE;
    }
    
    if (SUCCESS != initImageContainer(&self->imgContainer, &cfg->imageContainerCfg)) {
        LOGERR("initImageContainer() failed.");
        return FAILURE;
    }

    if (SUCCESS != initTextContainer(&self->textContainer, &cfg->textContainerCfg)) {
        LOGERR("initTextContainer() failed.");
        return FAILURE;
    }

    return SUCCESS;
}

void deinitRsrcMgr(struct RsrcMgr* self) {
    deinitImageContainer(&self->imgContainer);
    deinitTextContainer(&self->textContainer);
}

SDL_Texture* getImageTextureRsrcMgr(
    const struct RsrcMgr* self, int32_t rsrcId) {
    return getImageTextureImageContainer(&self->imgContainer, rsrcId);
}

const struct Vector* getImageFramesRsrcMgr(
    const struct RsrcMgr* self, int32_t rsrcId) {
    return getImageFramesImageContainer(&self->imgContainer, rsrcId);
}

SDL_Texture* getTextTextureRsrcMgr(
    const struct RsrcMgr* self, int32_t rsrcId) {
    return getTextTextureTextContainer(&self->textContainer, rsrcId);
}

void createTextRsrcMgr(struct RsrcMgr* self,
                             const char* text, const struct Color* color,
                             int32_t rsrcId, int32_t* outTextId,
                             int32_t* outTextWidth, int32_t* outTextHeight) {
    
    createTextTextContainer(&self->textContainer, text, color, 
                rsrcId, outTextId, outTextWidth, outTextHeight);
}

void unloadTextRsrcMgr(struct RsrcMgr* self,  int32_t textId) {
    unloadTextTextContainer(&self->textContainer, textId);
}

void reloadTextRsrcMgr(struct RsrcMgr* self,
                             const char* text, const struct Color* color,
                             int32_t rsrcId, int32_t textId,
                             int32_t* outTextWidth, int32_t* outTextHeight) {
    
    reloadTextTextContainer(&self->textContainer, text, color, 
                    rsrcId, textId, outTextWidth, outTextHeight);
}