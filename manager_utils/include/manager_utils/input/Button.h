#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_INPUT_BUTTON_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_INPUT_BUTTON_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */
#include "manager_utils/drawing/Image.h"

/* Forward declarations */
struct InputEvent;

/*        Defines       */

enum ButtonStates {
    UNCLICKED, CLICKED, DISABLED
};

struct Button {
    struct Image img;
    bool isInputUnlocked;
};

void createButton(struct Button *self, int32_t rsrcId, const struct Point *pos);

void resetButton(struct Button *self);

void drawButton(struct Button *self);

void lockInputButton(struct Button *self);

void unlockInputButton(struct Button *self);

bool containsEventButton(struct Button *self, const struct InputEvent *event);

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_INPUT_BUTTON_H_ */