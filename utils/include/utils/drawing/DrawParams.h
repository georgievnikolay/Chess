#ifndef UTILS_INCLUDE_UTILS_DRAWING_DRAWPARAMS_H_
#define UTILS_INCLUDE_UTILS_DRAWING_DRAWPARAMS_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "utils/drawing/Point.h"
#include "utils/drawing/Rectangle.h"
#include <stdint.h>

/* Forward declarations */

/*        Defines       */

typedef enum {
    BLEND_NONE  = 0, //value for SDL_BLENDMODE_NONE
    BLEND_BLEND = 1, //value for SDL_BLENDMODE_BLEND
    BLEND_ADD   = 2, //value for SDL_BLENDMODE_ADD
    BLEND_MOD   = 4  //value for SDL_BLENDMODE_MODE
} BlendMode;

typedef enum {
    IMAGE_WIDGET,
    TEXT_WIDGET,
    UNKNOWN_WIDGET_TYPE
} WidgetType;

typedef enum {
    NONE_WIDGET_FLIP,
    HORIZONTAL_WIDGET_FLIP,
    VERTICAL_WIDGET_FLIP,
    HORIZONTAL_AND_VERTICAL_WIDGET_FLIP
} WidgetFlip;

extern const int32_t INVALID_RSRC_ID;

extern const int32_t FULL_OPACITY;
extern const int32_t ZERO_OPACITY;

struct DrawParams {
    //Top left position of texture
    struct Point pos;

    //Draw dimensions of the texture
    int32_t width;
    int32_t height;

    struct Rectangle frameRect;
    
    double rotationAngle;
    struct Point rotationCenter;

    int32_t opacity;

    BlendMode blendMode;

    WidgetFlip flipType;

    //unique resourceId
    union {
      int32_t rsrcId;
      int32_t textId;
    };

    WidgetType widgetType;
};

void resetDrawParams(struct DrawParams* drawParams);

#endif /* UTILS_INCLUDE_UTILS_DRAWING_DRAWPARAMS_H_ */