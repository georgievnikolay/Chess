#ifndef INCLUDE_GAME_ENTITIES_PANELS_GAMEPANELS_H_
#define INCLUDE_GAME_ENTITIES_PANELS_GAMEPANELS_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "game/entities/panels/PiecePromotionPanel.h"
#include "game/entities/panels/GameStatePanel.h"

/* Forward declarations */
struct GamePanelsCfg;
struct InputEvent;

/*        Defines       */

struct GamePanels {
    struct PiecePromotionPanel piecePromotionPanel;
    struct GameStatePanel gameStatePanel;
};

int32_t initGamePanels(struct GamePanels* self, const struct GamePanelsCfg* cfg, void* proxy);

void deinitGamePanels(struct GamePanels* self);

void handleEventGameStatePanels(struct GamePanels* self, struct InputEvent* event);

void drawGamePanels(struct GamePanels* self);

#endif /* INCLUDE_GAME_ENTITIES_PANELS_GAMEPANELS_H_ */