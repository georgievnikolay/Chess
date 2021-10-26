#ifndef INCLUDE_GAME_ENTITIES_HERO_H_
#define INCLUDE_GAME_ENTITIES_HERO_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "manager_utils/drawing/Image.h"

/* Forward declarations */
struct InputEvent;

/*        Defines       */
struct Hero {
    struct Image heroImg;
};

int32_t initHero(struct Hero* self, int32_t rsrcId);

void deinitHero(struct Hero* self);

void handleEventHero(struct Hero* self, struct InputEvent* event);

void drawHero(struct Hero* self);

#endif /* INCLUDE_GAME_ENTITIES_HERO_H_ */