/*      Own include     */
#include "utils/drawing/DrawParams.h"

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "utils/drawing/Point.h"

/* Forward declarations */

/*        Defines       */

const int32_t INVALID_RSRC_ID = -1;

const int32_t FULL_OPACITY = 255;
const int32_t ZERO_OPACITY = 0;

void resetDrawParams(struct DrawParams* drawParams) {
    drawParams->pos = POINT_UNDEFINED;
    drawParams->frameRect = RECTANGLE_ZERO;
    drawParams->rotationAngle = 0.0;
    drawParams->rotationCenter = POINT_ZERO;
    drawParams->width = 0;
    drawParams->height = 0;
    drawParams->opacity = FULL_OPACITY;
    drawParams->blendMode = BLEND_NONE;
    drawParams->flipType = NONE_WIDGET_FLIP;
    drawParams->rsrcId = INVALID_RSRC_ID;
    drawParams->widgetType = UNKNOWN_WIDGET_TYPE;
}