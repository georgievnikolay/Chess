/*      Own include     */
#include "engine/EngineConfigLoader.h"

/*    System includes   */
#include <stdlib.h>
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "common/TimerDefines.h"
#include "common/CommonDefines.h"
#include "utils/drawing/Rectangle.h"
#include "sdl_utils/config/ImageContainerCfg.h"

/* Forward declarations */

/*        Defines       */

static const int32_t SCREEN_WIDTH = 1024;
static const int32_t SCREEN_HEIGHT = 800;

static const int32_t RUNNING_GIRL_FRAMES_COUNT = 6;
static const int32_t RUNNING_GIRL_FRAME_ANIM_WIDTH = 256;
static const int32_t RUNNING_GIRL_FRAME_ANIM_HEIGHT = 220;

static const int32_t WHEEL_WIDTH_HEIGHT = 695;

static const int32_t START_STOP_BUTTON_FRAMES_COUNT = 3;
static const int32_t START_STOP_BUTTON_WIDTH = 150;
static const int32_t START_STOP_BUTTON_HEIGHT = 50;

static const int32_t ANGELINE_VINTAGE_FONT = 40;

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
    cfg->windowName = "Hardware_Rendering";
}

static void populateImageContainerConfig(struct ImageContainerCfg* cfg) {
    struct ImageConfig imgCfg;
    initVector(&imgCfg.frames, 10);
    struct Rectangle* frame;

    //Hero
    for (int32_t i = 0; i < RUNNING_GIRL_FRAMES_COUNT; i++) {
        frame = (struct Rectangle*)malloc(sizeof(struct Rectangle));
        frame->x = 0 + (RUNNING_GIRL_FRAME_ANIM_WIDTH * i);
        frame->y = 0;
        frame->w = RUNNING_GIRL_FRAME_ANIM_WIDTH;
        frame->h = RUNNING_GIRL_FRAME_ANIM_HEIGHT;

        pushElementVector(&imgCfg.frames, frame);
    }

    populateResourceLocation(imgCfg.location, "resources/images/sprites/running_girl.png");
    insertImageConfig(cfg, RUNNING_GIRL_ID, &imgCfg);
    clearElementsVector(&imgCfg.frames);

    //Wheel
    frame = (struct Rectangle*)malloc(sizeof(struct Rectangle));
    frame->x = 0;
    frame->y = 0;
    frame->w = WHEEL_WIDTH_HEIGHT;
    frame->h = WHEEL_WIDTH_HEIGHT;
    pushElementVector(&imgCfg.frames, frame);
    
    populateResourceLocation(imgCfg.location, "resources/images/wheel.png");
    insertImageConfig(cfg, WHEEL_ID, &imgCfg);
    clearElementsVector(&imgCfg.frames);
    
    //Buttons
#define BUTTONS_COUNT 2
    char* buttonLocation[BUTTONS_COUNT] = {
        "resources/buttons/button_start.png", 
        "resources/buttons/button_stop.png"};

    const int32_t buttonIds[BUTTONS_COUNT] = {
        START_BUTTON_ID, 
        STOP_BUTTON_ID};

    for (int32_t buttonId = 0; buttonId < BUTTONS_COUNT; buttonId++) {
        for (int32_t i = 0; i < START_STOP_BUTTON_FRAMES_COUNT; i++) {
            frame = (struct Rectangle*)malloc(sizeof(struct Rectangle));
            frame->x = 0 + (START_STOP_BUTTON_WIDTH * i);
            frame->y = 0;
            frame->w = START_STOP_BUTTON_WIDTH;
            frame->h = START_STOP_BUTTON_HEIGHT;

            pushElementVector(&imgCfg.frames, frame);
        }

        populateResourceLocation(imgCfg.location, buttonLocation[buttonId]);
        insertImageConfig(cfg, buttonIds[buttonId], &imgCfg);
        clearElementsVector(&imgCfg.frames);
    }
#undef BUTTONS_COUNT

    freeVector(&imgCfg.frames);
}

static void populateTextContainerConfig(struct TextContainerCfg* cfg) {
    struct FontConfig fontCfg;
    fontCfg.fontSize = ANGELINE_VINTAGE_FONT;
    populateResourceLocation(fontCfg.location, "resources/fonts/AngelineVintage.ttf");
    insertFontConfig(cfg, ANGELINE_VINTAGE_40_FONT_ID, &fontCfg);
}

static void populateManagerHandlerCfg(struct ManagerHandlerCfg* cfg) {
    populateWindowCfg(&cfg->drawMgrCfg.windowCfg);
    populateImageContainerConfig(&cfg->rscrMgrCfg.imageContainerCfg);
    populateTextContainerConfig(&cfg->rscrMgrCfg.textContainerCfg);
    
    cfg->drawMgrCfg.maxFrames = ENGINE_TARGET_FRAMES;
}

static void populateGameCfg(struct GameCfg* cfg) {
    cfg->heroRsrcId = RUNNING_GIRL_ID;
    cfg->wheelRsrcId = WHEEL_ID;
    cfg->startButtonRsrcId = START_BUTTON_ID;
    cfg->stopButtonRsrcId = STOP_BUTTON_ID;
    cfg->rotWheelTimerId = WHEEL_TIMER_ID;
}

struct EngineConfig loadEngineConfig() {
    struct EngineConfig cfg;
    memset(&cfg, 0, sizeof(struct EngineConfig));
    
    populateManagerHandlerCfg(&cfg.managerHandlerCfg);
    populateGameCfg(&cfg.gameCfg);

    cfg.debugConsoleFontId = ANGELINE_VINTAGE_40_FONT_ID;

    return cfg;
}