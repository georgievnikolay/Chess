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

static const int32_t SCREEN_WIDTH = 1024;
static const int32_t SCREEN_HEIGHT = 800;

static const int32_t CHESS_BOARD_IMG_WIDTH_HEIGHT = 800;

static const int32_t CHESS_PIECE_FRAMES_COUNT = 6;
static const int32_t CHESS_PIECE_FRAME_WIDTH_HEIGHT = 100;

static const int32_t MOVE_TILES_FRAMES_COUNT = 3;
static const int32_t MOVE_TILES_FRAME_WIDTH_HEIGHT = 100;

static const int32_t PROMOTION_BUTTON_FRAMES_COUNT = 2;
static const int32_t PROMOTION_BUTTON_FRAME_WIDTH_HEIGHT = 104;

static const int32_t TARGET_WIDTH_HEIGHT = 101;

static const int32_t ANGELINE_VINTAGE_FONT = 20;

static const int64_t ENGINE_TARGET_FRAMES = 30;

static void populateResourceLocation(char* buffer, char* relativePath) {
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
    cfg->windowName = "CHESS";
}

static void populateImageContainerConfig(struct ImageContainerCfg* cfg) {
    struct ImageConfig imgCfg;
    initVector(&imgCfg.frames, 10);
    struct Rectangle* frame;

//TODO: find better way to populate
    //Chess Board
    frame = (struct Rectangle*)malloc(sizeof(struct Rectangle));
    frame->x = 0;
    frame->y = 0;
    frame->w = CHESS_BOARD_IMG_WIDTH_HEIGHT;
    frame->h = CHESS_BOARD_IMG_WIDTH_HEIGHT;
    pushElementVector(&imgCfg.frames, frame);
    
    populateResourceLocation(imgCfg.location, "resources/images/ChessBoard.jpg");
    insertImageConfig(cfg, CHESS_BOARD_TEXTURE_ID, &imgCfg);
    clearElementsVector(&imgCfg.frames);

    //Target
    frame = (struct Rectangle*)malloc(sizeof(struct Rectangle));
    frame->x = 0;
    frame->y = 0;
    frame->w = TARGET_WIDTH_HEIGHT;
    frame->h = TARGET_WIDTH_HEIGHT;
    pushElementVector(&imgCfg.frames, frame);
    
    populateResourceLocation(imgCfg.location, "resources/images/Target.png");
    insertImageConfig(cfg, TARGET_TEXTURE_ID, &imgCfg);
    clearElementsVector(&imgCfg.frames);

    //Chess Pieces
#define PLAYERS_COUNT 2
    char* buttonLocation[PLAYERS_COUNT] = {
        "resources/images/Whites.png",
        "resources/images/Blacks.png"};

    const int32_t buttonIds[PLAYERS_COUNT] = {
        WHITE_PIECES_TEXTURE_ID,
        BLACK_PIECES_TEXTURE_ID};

    for (int32_t buttonId = 0; buttonId < PLAYERS_COUNT; buttonId++) {
        for (int32_t i = 0; i < CHESS_PIECE_FRAMES_COUNT; i++) {
            frame = (struct Rectangle*)malloc(sizeof(struct Rectangle));
            frame->x = 0 + (CHESS_PIECE_FRAME_WIDTH_HEIGHT * i);
            frame->y = 0;
            frame->w = CHESS_PIECE_FRAME_WIDTH_HEIGHT;
            frame->h = CHESS_PIECE_FRAME_WIDTH_HEIGHT;

            pushElementVector(&imgCfg.frames, frame);
        }

        populateResourceLocation(imgCfg.location, buttonLocation[buttonId]);
        insertImageConfig(cfg, buttonIds[buttonId], &imgCfg);
        clearElementsVector(&imgCfg.frames);
    }
#undef BUTTONS_COUNT

    //Move Tiles
    for (int32_t i = 0; i < MOVE_TILES_FRAMES_COUNT; i++) {
            frame = (struct Rectangle*)malloc(sizeof(struct Rectangle));
            frame->x = 0 + (MOVE_TILES_FRAME_WIDTH_HEIGHT * i);
            frame->y = 0;
            frame->w = MOVE_TILES_FRAME_WIDTH_HEIGHT;
            frame->h = MOVE_TILES_FRAME_WIDTH_HEIGHT;

            pushElementVector(&imgCfg.frames, frame);
        }
        populateResourceLocation(imgCfg.location, "resources/images/MoveTiles.png");
        insertImageConfig(cfg, MOVE_TILES_TEXTURE_ID, &imgCfg);
        clearElementsVector(&imgCfg.frames);

    //Piece prom button
    for (int32_t i = 0; i < PROMOTION_BUTTON_FRAMES_COUNT; i++) {
            frame = (struct Rectangle*)malloc(sizeof(struct Rectangle));
            frame->x = 0 + (PROMOTION_BUTTON_FRAME_WIDTH_HEIGHT * i);
            frame->y = 0;
            frame->w = PROMOTION_BUTTON_FRAME_WIDTH_HEIGHT;
            frame->h = PROMOTION_BUTTON_FRAME_WIDTH_HEIGHT;

            pushElementVector(&imgCfg.frames, frame);
        } //TODO: remove or keep piecePromoteButtonBgr1
        populateResourceLocation(imgCfg.location, "resources/images/piecePromoteButtonBgr1.png");
        insertImageConfig(cfg, PIECE_PROMOTION_BUTTON_TEXTURE_ID, &imgCfg);
        clearElementsVector(&imgCfg.frames);

    freeVector(&imgCfg.frames);
}

static void populateTextContainerConfig(struct TextContainerCfg* cfg) {
    struct FontConfig fontCfg;
    fontCfg.fontSize = ANGELINE_VINTAGE_FONT;
    populateResourceLocation(fontCfg.location, "resources/fonts/AngelineVintage.ttf");
    insertFontConfig(cfg, ANGELINE_VINTAGE_20_FONT_ID, &fontCfg);
}

static void populateManagerHandlerCfg(struct ManagerHandlerCfg* cfg) {
    populateWindowCfg(&cfg->drawMgrCfg.windowCfg);
    populateImageContainerConfig(&cfg->rscrMgrCfg.imageContainerCfg);
    populateTextContainerConfig(&cfg->rscrMgrCfg.textContainerCfg);
    
    cfg->drawMgrCfg.maxFrames = ENGINE_TARGET_FRAMES;
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

static void populateGameCfg(struct GameCfg* cfg) {
    cfg->gameBoardRsrcId = CHESS_BOARD_TEXTURE_ID;
    cfg->targetRsrcId = TARGET_TEXTURE_ID;
    cfg->moveSelectorRsrcId = MOVE_TILES_TEXTURE_ID;
    
    cfg->pieceHandlerCfg.whitePiecesRsrcId = WHITE_PIECES_TEXTURE_ID;
    cfg->pieceHandlerCfg.blackPiecesRsrcId = BLACK_PIECES_TEXTURE_ID;
    // cfg->pieceHandlerCfg.notReadyFontId = ANGELINE_VINTAGE_20_FONT_ID;

    populatePiecePromotionPanelCfg(&cfg->piecePromotionPanelCfg);
}

struct EngineConfig loadEngineConfig() {
    struct EngineConfig cfg;
    memset(&cfg, 0, sizeof(struct EngineConfig));
    
    populateManagerHandlerCfg(&cfg.managerHandlerCfg);
    populateGameCfg(&cfg.gameCfg);

    cfg.debugConsoleFontId = ANGELINE_VINTAGE_20_FONT_ID;

    return cfg;
}