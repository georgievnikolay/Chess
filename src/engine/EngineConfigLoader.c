/*      Own include     */
#include "engine/EngineConfigLoader.h"

/*    System includes   */
#include <stdlib.h>
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "common/TimerDefines.h"
#include "common/CommonDefines.h"
#include "sdl_utils/config/ImageContainerCfg.h"
#include "utils/drawing/Rectangle.h"
#include "utils/ErrorCodes.h"

/* Forward declarations */

/*        Defines       */

//TODO: nice idea for one populate function
// #define GET_PARAMS(name) name ## FRAMES_COUNT

static void populateResourceLocation(char* buffer, const char* relativePath) {
#ifdef RELEASE_BUILD
    strcpy(buffer, relativePath);
#else
    strcpy(buffer, "../");
    strcat(buffer, relativePath);
#endif
}

static void populateWindowCfg(struct MonitorWindowCfg* cfg) {
    cfg->mode = WINDOW_SHOWN;
    cfg->width = SCREEN_WIDTH;
    cfg->height = SCREEN_HEIGHT;
    cfg->windowPos = POINT_UNDEFINED;
    cfg->windowName = SCREEN_NAME;
}

static void populateFrames(struct ImageConfig* imgCfg, struct ImageContainerCfg* cfg,
                           const char* filePath, 
                           int32_t frameWidth, int32_t frameHeight, 
                           int32_t framesCount, TextureIds textureId) {
    
    struct Rectangle* frame;
    for (int32_t i = 0; i < framesCount; i++) {
            frame = (struct Rectangle*)malloc(sizeof(struct Rectangle));
            frame->x = 0 + (frameWidth * i);
            frame->y = 0;
            frame->w = frameWidth;
            frame->h = frameHeight;

            pushElementVector(&imgCfg->frames, frame);
        }

    populateResourceLocation(imgCfg->location, filePath);
    insertImageConfig(cfg, textureId, imgCfg);
    clearElementsVector(&imgCfg->frames);
}

static void populateImageContainerConfig(struct ImageContainerCfg* cfg) {
    struct ImageConfig imgCfg;
    initVector(&imgCfg.frames, 10);

//Chess Board
    populateFrames(&imgCfg, cfg, "resources/images/ChessBoard.jpg", 
                    CHESS_BOARD_IMG_WIDTH_HEIGHT, 
                    CHESS_BOARD_IMG_WIDTH_HEIGHT, 
                    CHESS_BOARD_IMG_FRAMES_COUNT, CHESS_BOARD_TEXTURE_ID);

//Target
    populateFrames(&imgCfg, cfg, "resources/images/Target.png", 
                    TARGET_WIDTH_HEIGHT, 
                    TARGET_WIDTH_HEIGHT, 
                    TARGET_FRAMES_COUNT, TARGET_TEXTURE_ID);

//Chess Pieces
#define PLAYERS_COUNT 2
    char* piecesLocation[PLAYERS_COUNT] = {
        "resources/images/Whites.png",
        "resources/images/Blacks.png"};

    const int32_t piecesIds[PLAYERS_COUNT] = {
        WHITE_PIECES_TEXTURE_ID,
        BLACK_PIECES_TEXTURE_ID};

    for (int32_t pieceId = 0; pieceId < PLAYERS_COUNT; pieceId++) {
        populateFrames(&imgCfg, cfg, piecesLocation[pieceId], 
                       CHESS_PIECE_FRAME_WIDTH_HEIGHT, 
                       CHESS_PIECE_FRAME_WIDTH_HEIGHT, 
                       CHESS_PIECE_FRAMES_COUNT, piecesIds[pieceId]);
    }
#undef PLAYERS_COUNT

//Move Tiles
    populateFrames(&imgCfg, cfg, "resources/images/MoveTiles.png", 
                   MOVE_TILES_FRAME_WIDTH_HEIGHT, 
                   MOVE_TILES_FRAME_WIDTH_HEIGHT, 
                   MOVE_TILES_FRAMES_COUNT, MOVE_TILES_TEXTURE_ID);

//Piece prom button
    populateFrames(&imgCfg, cfg, "resources/images/piecePromoteButtonBgr1.png", 
                   PROMOTION_BUTTON_FRAME_WIDTH_HEIGHT, 
                   PROMOTION_BUTTON_FRAME_WIDTH_HEIGHT, 
                   PROMOTION_BUTTON_FRAMES_COUNT, PIECE_PROMOTION_BUTTON_TEXTURE_ID);               

//Game Buttons
#define GAME_BUTTONS_COUNT 4
    char* buttonsLocation[GAME_BUTTONS_COUNT] = {
        "resources/buttons/start_game_button.png",
        "resources/buttons/continue_game_button.png",
        "resources/buttons/exit_game_button.png",
        "resources/buttons/quit_game_button.png"};

    const int32_t buttonIds[GAME_BUTTONS_COUNT] = {
        START_GAME_BUTTON_TEXTURE_ID,
        CONTINUE_GAME_BUTTON_TEXTURE_ID,
        EXIT_GAME_BUTTON_TEXTURE_ID,
        QUIT_GAME_BUTTON_TEXTURE_ID};
    
    for (int32_t buttonId = 0; buttonId < GAME_BUTTONS_COUNT; buttonId++) {
        populateFrames(&imgCfg, cfg, buttonsLocation[buttonId], 
                       GAME_BUTTONS_FRAME_WIDTH, 
                       GAME_BUTTONS_FRAME_HEIGHT, 
                       GAME_BUTTONS_FRAMES_COUNT, buttonIds[buttonId]); 
    }      
#undef GAME_BUTTONS_COUNT

//Start Game Image
    populateFrames(&imgCfg, cfg, "resources/images/chess_start_screen1.jpg", 
                    START_GAME_IMAGE_WIDTH, 
                    START_GAME_IMAGE_HEIGHT, 
                    START_GAME_IMAGE_FRAMES_COUNT, START_SCREEN_TEXTURE_ID);

    freeVector(&imgCfg.frames);
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