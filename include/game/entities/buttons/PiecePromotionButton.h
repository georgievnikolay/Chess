#ifndef INCLUDE_GAME_ENTITIES_BUTTONS_PIECEPROMOTIONBUTTON_H_
#define INCLUDE_GAME_ENTITIES_BUTTONS_PIECEPROMOTIONBUTTON_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "game/config/PiecePromotionButtonCfg.h"
#include "manager_utils/input/Button.h"
#include "manager_utils/drawing/Image.h"

/* Forward declarations */
struct InputEvent;

/*        Defines       */

struct PiecePromotionButton {
    struct Button button;
    struct Image bgrImg;
    struct PiecePromotionButtonCfg cfg;
    void* panelProxy;
};

int32_t initPiecePromotionButton(struct PiecePromotionButton *self,
                                 const struct PiecePromotionButtonCfg *cfg,
                                 void* panelProxy);

void deinitPiecePromotionButton(struct PiecePromotionButton *self);

void handleEventPiecePromotionButton(struct PiecePromotionButton *self,
                                     const struct InputEvent *event);

void drawPiecePiecePromotionButton(struct PiecePromotionButton *self);

void activatePiecePromotionButton(struct PiecePromotionButton *self, 
                                  int32_t playerId);

#endif /* INCLUDE_GAME_ENTITIES_BUTTONS_PIECEPROMOTIONBUTTON_H_ */