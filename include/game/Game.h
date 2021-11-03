#ifndef INCLUDE_GAME_GAME_H_
#define INCLUDE_GAME_GAME_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "game/config/GameCfg.h"
#include "game/entities/PiecePromotionPanel.h"
#include "game/entities/board/GameBoard.h"
#include "game/entities/board/GameBoardAnimator.h"
#include "game/entities/pieces/PieceHandler.h"
#include "game/logic/InputInverter.h"
#include "game/logic/GameLogic.h"

/* Forward declarations */
struct InputEvent;

/*        Defines       */

struct Game {
    struct GameBoard gameBoard;
    struct PieceHandler pieceHandler;
    struct PiecePromotionPanel piecePromotionPanel;
    struct GameLogic gameLogic;
    struct GameBoardAnimator gameBoardAnimator;
    struct InputInverter inputInverter;
};

int32_t initGame(struct Game* self, const struct GameCfg* cfg);

void deinitGame(struct Game* self);

void handleEventGame(struct Game* self, struct InputEvent* event);

void drawGame(struct Game* self);

#endif /* INCLUDE_GAME_GAME_H_ */