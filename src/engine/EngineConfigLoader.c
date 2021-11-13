/*      Own include     */
#include "engine/EngineConfigLoader.h"

/*    System includes   */
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "common/TimerDefines.h"
#include "engine/FramePopulator.h"
#include "sdl_utils/config/ImageContainerCfg.h"
#include "utils/ErrorCodes.h"

/* Forward declarations */

/*        Defines       */

static void populateWindowCfg(struct MonitorWindowCfg* cfg) {
    cfg->mode = WINDOW_SHOWN;
    cfg->width = SCREEN_WIDTH;
    cfg->height = SCREEN_HEIGHT;
    cfg->windowPos = POINT_UNDEFINED;
    cfg->windowName = SCREEN_NAME;
}

static void populateTextContainerConfig(struct TextContainerCfg* cfg) {
    struct FontConfig fontCfg;

    fontCfg.fontSize = SERIFNCB_FONT_20;
    populateResourceLocation(fontCfg.location, "resources/fonts/SERIFNCB.TTF");
    insertFontConfig(cfg, SERIFNCB_20_FONT_ID, &fontCfg);

    fontCfg.fontSize = SERIFNCB_FONT_50;
    populateResourceLocation(fontCfg.location, "resources/fonts/SERIFNCB.TTF");
    insertFontConfig(cfg, SERIFNCB_50_FONT_ID, &fontCfg);

    fontCfg.fontSize = SERIFNCB_FONT_70;
    populateResourceLocation(fontCfg.location, "resources/fonts/SERIFNCB.TTF");
    insertFontConfig(cfg, SERIFNCB_70_FONT_ID, &fontCfg);
}

static void populateManagerHandlerCfg(struct ManagerHandlerCfg* cfg) {
    populateWindowCfg(&cfg->drawMgrCfg.windowCfg);
    populateImageContainerConfig(&cfg->rscrMgrCfg.imageContainerCfg);
    populateTextContainerConfig(&cfg->rscrMgrCfg.textContainerCfg);
    
    cfg->drawMgrCfg.maxFrames = ENGINE_TARGET_FRAMES;
}

static void populateGameStatePanelCfg(struct GameStatePanelCfg* cfg) {
    cfg->startButtonRsrcId = START_GAME_BUTTON_TEXTURE_ID;
    cfg->continueButtonRsrcId = CONTINUE_GAME_BUTTON_TEXTURE_ID;
    cfg->exitButtonRsrcId = EXIT_GAME_BUTTON_TEXTURE_ID;
    cfg->quitButtonRsrcId = QUIT_GAME_BUTTON_TEXTURE_ID;
    cfg->startScreenRsrcId = START_SCREEN_TEXTURE_ID;

    cfg->gameScreenWidth = SCREEN_WIDTH;
    cfg->gameScreenHeight = SCREEN_HEIGHT;
    
    cfg->gameBoardWidth_Height = CHESS_BOARD_IMG_WIDTH_HEIGHT;

    cfg->buttonWidth = GAME_BUTTONS_FRAME_WIDTH;
    cfg->buttonHeight = GAME_BUTTONS_FRAME_HEIGHT;
}

static void populatePiecePromotionPanelCfg(struct PiecePromotionPanelCfg* cfg) {
    cfg->whitePiecesRsrcId = WHITE_PIECES_TEXTURE_ID;
    cfg->blackPiecesRsrcId = BLACK_PIECES_TEXTURE_ID;
    cfg->buttonBgrRsrcId = PIECE_PROMOTION_BUTTON_TEXTURE_ID;

    cfg->gameBoardWidth = CHESS_BOARD_IMG_WIDTH_HEIGHT;
    cfg->gameBoardHeight = CHESS_BOARD_IMG_WIDTH_HEIGHT;

    cfg->buttonBgrWidth = PROMOTION_BUTTON_FRAME_WIDTH_HEIGHT;
    cfg->buttonBgrHeight = PROMOTION_BUTTON_FRAME_WIDTH_HEIGHT;

    cfg->buttonWidth = TARGET_WIDTH_HEIGHT;
    cfg->buttonHeight = TARGET_WIDTH_HEIGHT;
}

static void populateGameLogicCfg(struct GameLogicCfg* cfg) {
    cfg->fontId = SERIFNCB_50_FONT_ID;

    cfg->screenWidth = SCREEN_WIDTH;
    cfg->screenHeight = SCREEN_HEIGHT;

    cfg->gameBoardWidth_Height = CHESS_BOARD_IMG_WIDTH_HEIGHT;
}

static void populateLogPanelCfg(struct LogPanelCfg* cfg) {
    cfg->fontId = SERIFNCB_20_FONT_ID;

    cfg->screenWidth = SCREEN_WIDTH;
    cfg->screenHeight = SCREEN_HEIGHT;

    cfg->gameBoardWidth = CHESS_BOARD_IMG_WIDTH_HEIGHT;
    cfg->gameBoardHeight = CHESS_BOARD_IMG_WIDTH_HEIGHT;
}

static void populatePieceHandlerCfg(struct PieceHandlerCfg* cfg) {
    cfg->whitePiecesRsrcId = WHITE_PIECES_TEXTURE_ID;
    cfg->blackPiecesRsrcId = BLACK_PIECES_TEXTURE_ID;

    cfg->pieceHandlerHelperCfg.fontId = SERIFNCB_70_FONT_ID;
    cfg->pieceHandlerHelperCfg.gameBoardWidth = CHESS_BOARD_IMG_WIDTH_HEIGHT;
    cfg->pieceHandlerHelperCfg.gameBoardHeight = CHESS_BOARD_IMG_WIDTH_HEIGHT;

    populateLogPanelCfg(&cfg->logPanelCfg);
}

static void populateGameCfg(struct GameCfg* cfg) {
    cfg->gameBoardRsrcId = CHESS_BOARD_TEXTURE_ID;
    cfg->targetRsrcId = TARGET_TEXTURE_ID;
    cfg->moveSelectorRsrcId = MOVE_TILES_TEXTURE_ID;
    
    populatePieceHandlerCfg(&cfg->pieceHandlerCfg);
    populateGameLogicCfg(&cfg->gameLogicCfg);
    populateGameStatePanelCfg(&cfg->gameStatePanelCfg);
    populatePiecePromotionPanelCfg(&cfg->piecePromotionPanelCfg);
}

struct EngineConfig loadEngineConfig() {
    struct EngineConfig cfg;
    memset(&cfg, 0, sizeof(struct EngineConfig));
    
    populateManagerHandlerCfg(&cfg.managerHandlerCfg);
    populateGameCfg(&cfg.gameCfg);

    cfg.debugConsoleFontId = SERIFNCB_50_FONT_ID;

    return cfg;
}