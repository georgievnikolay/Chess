/*      Own include     */
#include "engine/FramePopulator.h"

/*    System includes   */
#include <stdlib.h>
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "utils/path/PathConfigurator.h"
#include "sdl_utils/config/ImageContainerCfg.h"
#include "utils/drawing/Rectangle.h"

/* Forward declarations */

/*        Defines       */

void populateResourceLocation(char* buffer, const char* relativePath) {
#ifdef RELEASE_BUILD
    strcpy(buffer, relativePath);
#else
    strcpy(buffer, "../");
    strcat(buffer, relativePath);
#endif
    configurePath(buffer);
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

void populateImageContainerConfig(struct ImageContainerCfg* cfg) {
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