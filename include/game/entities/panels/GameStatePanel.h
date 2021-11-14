#ifndef INCLUDE_GAME_ENTITIES_GAMESTATEPANEL_H_
#define INCLUDE_GAME_ENTITIES_GAMESTATEPANEL_H_

/*      Own include     */

/*    System includes   */
#include <stdbool.h>
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "game/defines/GameDefines.h"
#include "game/entities/buttons/GameButton.h"

/* Forward declarations */
struct InputEvent;
struct GameStatePanelCfg;

/*        Defines       */

struct GameStatePanel {
    struct Image panelImg;
    struct GameButton gameButtons[GAME_BUTTONS_COUNT];
    void *gameProxy;
    bool isActive;
};

int32_t initGameStatePanel(struct GameStatePanel* self,
                           const struct GameStatePanelCfg* cfg,
                           void* gameProxy);

void deinitGameStatePanel(struct GameStatePanel* self);

void handleEventGameStatePanel(struct GameStatePanel* self,
                               struct InputEvent* event);

void drawGameStatePanel(struct GameStatePanel* self);

void activateGameStatePanel(struct GameStatePanel* self);

#endif /* INCLUDE_GAME_ENTITIES_GAMESTATEPANEL_H_ */