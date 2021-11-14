#ifndef INCLUDE_GAME_ENTITIES_PIECEPROMOTIONPANEL_H_
#define INCLUDE_GAME_ENTITIES_PIECEPROMOTIONPANEL_H_

/*      Own include     */

/*    System includes   */
#include <stdbool.h>
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "game/entities/buttons/PiecePromotionButton.h"

/* Forward declarations */
struct InputEvent;
struct PiecePromotionPanelCfg;

/*        Defines       */

enum PiecePromotionPanelDefines {
    PROMOTE_BUTTONS_COUNT = 4
};

struct PiecePromotionPanel {
    struct PiecePromotionButton promotionBtns[PROMOTE_BUTTONS_COUNT];
    void *gameProxy;
    bool isActive;
};

int32_t initPiecePromotionPanel(struct PiecePromotionPanel* self,
                                const struct PiecePromotionPanelCfg* cfg,
                                void* gameProxy);

void deinitPiecePromotionPanel(struct PiecePromotionPanel* self);

void handleEventPiecePromotionPanel(struct PiecePromotionPanel* self,
                                    const struct InputEvent* event);

void drawPiecePromotionPanel(struct PiecePromotionPanel* self);

void activatePiecePromotionPanel(struct PiecePromotionPanel* self, int32_t playerId);


#endif /* INCLUDE_GAME_ENTITIES_PIECEPROMOTIONPANEL_H_ */