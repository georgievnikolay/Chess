#ifndef INCLUDE_GAME_LOGIC_INPUTINVERTER_H_
#define INCLUDE_GAME_LOGIC_INPUTINVERTER_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "utils/drawing//DrawParams.h"

/* Forward declarations */
struct InputEvent;

/*        Defines       */

struct InputInverter {
    int32_t boardWidth;
    int32_t boardHeight;
    WidgetFlip flipType;
};

int32_t initInputInverter(struct InputInverter* self, 
                          int32_t boardWidth,
                          int32_t boardHeight);

void invertEventInputInverter(struct InputInverter* self,
                              struct InputEvent *inputEvent);

void setFlipTypetInputInverter(struct InputInverter* self,
                               WidgetFlip flipType);

#endif /* INCLUDE_GAME_LOGIC_INPUTINVERTER_H_ */