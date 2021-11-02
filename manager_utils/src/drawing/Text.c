/*      Own include     */
#include "manager_utils/drawing/Text.h"

/*    System includes   */
#include <stdlib.h>
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "manager_utils/drawing/Widget.h"
#include "manager_utils/managers/RsrcMgr.h"
#include "utils/Log.h"
#include "utils/drawing/Color.h"
#include "utils/drawing/DrawParams.h"

/* Forward declarations */

/*        Defines       */

static void copyTextContent(char** currText, const char* newText) {
    if (*currText != NULL) {
        free(*currText);
    }

    *currText = (char *)malloc(strlen(newText) + 1);
    strcpy(*currText, newText);
}

void createText(struct Text *self, const char *textContent, int32_t fontId,
                const struct Color *color, const struct Point *pos) {

    if (self->widget.isCreated) {
        LOGERR("Error, Text with rsrcId: %d and fontId %d, was already created!"
            " Will not re-create!", self->widget.drawParams.textId, fontId);
        return;        
    }
    resetWidget(&self->widget);

    struct DrawParams* params = &self->widget.drawParams;
    params->pos = *pos;
    params->widgetType = TEXT_WIDGET;

    self->fontId = fontId;
    self->color = *color;
    self->textContent = NULL;
    copyTextContent(&self->textContent, textContent);

    createTextRsrcMgr(gRsrcMgr, self->textContent, color, 
                        self->fontId, &params->textId, 
                        &params->width, &params->height);

    params->frameRect.x = 0;
    params->frameRect.y = 0;
    params->frameRect.w = params->width;
    params->frameRect.h = params->height;
    
    self->widget.isCreated = true;
    self->widget.isDestroyed = false;
}

void destroyText(struct Text *self) {
    if (self->widget.isDestroyed) {
        LOGERR("Error, Text with textId: %d, was already destroyed!", 
                self->widget.drawParams.textId);
        return;        
    }

    if (self->textContent) {
        free(self->textContent);
        self->textContent = NULL;
    }

    resetText(self);
    self->widget.isDestroyed = true;
    self->widget.isCreated = false;
}

void resetText(struct Text *self) {
    resetWidget(&self->widget);
    self->color = COLOR_BLACK;
    self->fontId = INVALID_RSRC_ID;
    self->textContent = NULL;
}

void setText(struct Text *self, const char *textContent) {
    if (!self->widget.isCreated) {
        LOGERR("Error, Text with fontId: %d, was not created!", 
                self->fontId);
        return;        
    }
    if (0 == (strcmp(self->textContent, textContent))) {
        return;
    }

    copyTextContent(&self->textContent, textContent);

    struct DrawParams* params = &self->widget.drawParams;
    reloadTextRsrcMgr(gRsrcMgr, self->textContent, &self->color, 
                        self->fontId, params->textId, 
                        &params->width, &params->height);
    
    params->frameRect.w = params->width;
    params->frameRect.h = params->height;
}

void setColorText(struct Text *self, const struct Color *color) {
    if (!self->widget.isCreated) {
        LOGERR("Error, Text with fontId: %d, was not created!", 
                self->fontId);
        return;        
    }
    if (areColorsEqual(&self->color, color)) {
        return;
    }

    self->color = *color;

    struct DrawParams* params = &self->widget.drawParams;
    reloadTextRsrcMgr(gRsrcMgr, self->textContent, &self->color, 
                        self->fontId, params->textId, 
                        &params->width, &params->height);
}

void drawText(struct Text *self) {
    drawWidget(&self->widget);
}