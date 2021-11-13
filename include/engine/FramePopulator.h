#ifndef INCLUDE_ENGINE_FRAMEPOPULATOR_H_
#define INCLUDE_ENGINE_FRAMEPOPULATOR_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "common/CommonDefines.h"

/* Forward declarations */
struct ImageContainerCfg;

/*        Defines       */

#define SCREEN_NAME "CHESS"

static const int32_t SCREEN_WIDTH = 1280;
static const int32_t SCREEN_HEIGHT = 800;

static const int32_t START_GAME_IMAGE_FRAMES_COUNT = 1;
static const int32_t START_GAME_IMAGE_WIDTH = 1280;
static const int32_t START_GAME_IMAGE_HEIGHT = 800;

static const int32_t CHESS_BOARD_IMG_FRAMES_COUNT = 1;
static const int32_t CHESS_BOARD_IMG_WIDTH_HEIGHT = 800;

static const int32_t CHESS_PIECE_FRAMES_COUNT = 6;
static const int32_t CHESS_PIECE_FRAME_WIDTH_HEIGHT = 100;

static const int32_t MOVE_TILES_FRAMES_COUNT = 3;
static const int32_t MOVE_TILES_FRAME_WIDTH_HEIGHT = 100;

static const int32_t PROMOTION_BUTTON_FRAMES_COUNT = 2;
static const int32_t PROMOTION_BUTTON_FRAME_WIDTH_HEIGHT = 104;

static const int32_t GAME_BUTTONS_FRAMES_COUNT = 3;
static const int32_t GAME_BUTTONS_FRAME_WIDTH = 229;
static const int32_t GAME_BUTTONS_FRAME_HEIGHT = 66;

static const int32_t TARGET_FRAMES_COUNT = 1;
static const int32_t TARGET_WIDTH_HEIGHT = 101;

static const int32_t SERIFNCB_FONT_20 = 20;
static const int32_t SERIFNCB_FONT_50 = 50;
static const int32_t SERIFNCB_FONT_70 = 70;

static const int64_t ENGINE_TARGET_FRAMES = 30;


void populateResourceLocation(char* buffer, const char* relativePath);

void populateImageContainerConfig(struct ImageContainerCfg* cfg);

#endif /* INCLUDE_ENGINE_FRAMEPOPULATOR_H_ */