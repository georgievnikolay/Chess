/*      Own include     */
#include "manager_utils/managers/DrawMgr.h"

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "manager_utils/managers/RsrcMgr.h"
#include "manager_utils/managers/config/DrawMgrCfg.h"
#include "sdl_utils/Texture.h"
#include "utils/Log.h"
#include "utils/ErrorCodes.h"

/* Forward declarations */

/*        Defines       */
struct DrawMgr *gDrawMgr = NULL;

static SDL_Texture* getTexture(const struct DrawParams* drawParams) {
    if (IMAGE_WIDGET == drawParams->widgetType) {
        return getImageTextureRsrcMgr(gRsrcMgr, drawParams->rsrcId);
    }
    
    if (TEXT_WIDGET == drawParams->widgetType) {
        return getTextTextureRsrcMgr(gRsrcMgr, drawParams->textId);
    }
    
    LOGERR("Recieved invalid widgetType: %d for rsrcId %d", 
            drawParams->widgetType, drawParams->rsrcId);
    return NULL;
}

int32_t initDrawMgr(struct DrawMgr* self, const struct DrawMgrCfg* cfg) {
    if (self == NULL) {
        LOGERR("Error NULL provided for gDrawMgr");
        return FAILURE;
    }

    if (SUCCESS != initMonitorWindow(&gDrawMgr->window, &cfg->windowCfg)) {
        LOGERR("initMonitorWindow() failed.");
        return FAILURE;
    }

    if (SUCCESS != initRenderer(&gDrawMgr->renderer, self->window.sdlWindow)) {
        LOGERR("initRenderer() failed.");
        return FAILURE;
    }

    self->maxFrames = cfg->maxFrames;

    return SUCCESS;
}

void deinitDrawMgr(struct DrawMgr* self) {
    deinitRenderer(&self->renderer);
    deinitMonitorWindow(&self->window);
}

void clearScreenDrawMgr(struct DrawMgr* self) {
    clearScreenRenderer(&self->renderer);
}

void finishFrameDrawMgr(struct DrawMgr* self) {
    finishFrameRenderer(&self->renderer);
}

void addDrawCmdDrawMgr(struct DrawMgr* self,
                       const struct DrawParams *drawParams) {
    SDL_Texture* texture = getTexture(drawParams);
    renderTexture(&self->renderer, drawParams, texture);
}

void setWidgetBlendModeDrawMgr(struct DrawMgr* self,
                               const struct DrawParams *drawParams,
                               BlendMode blendMode) {
    UNUSED(self);
    
    SDL_Texture* texture = getTexture(drawParams);
    if (SUCCESS != setBlendModeTexture(texture, blendMode)) {
        LOGERR("setBlendModeTexture() failed for rsrcId %d", 
                drawParams->rsrcId);
    }
}

void setWidgetOpacityDrawMgr(struct DrawMgr* self,
                             const struct DrawParams *drawParams) {
    UNUSED(self);

    if (drawParams->widgetType == IMAGE_WIDGET) {
        return;
    }
    
    SDL_Texture* texture = getTexture(drawParams);
    if (SUCCESS != setAlphaTexture(texture, drawParams->opacity)) {
        LOGERR("setBlendModeTexture() failed for rsrcId %d", 
                drawParams->rsrcId);        
    }
}
