#ifndef INCLUDE_COMMON_COMMONDEFINES_H_
#define INCLUDE_COMMON_COMMONDEFINES_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */

/* Forward declarations */

/*        Defines       */

typedef enum {
    WHITE_PIECES_TEXTURE_ID,
    BLACK_PIECES_TEXTURE_ID,
    CHESS_BOARD_TEXTURE_ID,
    TARGET_TEXTURE_ID,
    MOVE_TILES_TEXTURE_ID,
    PIECE_PROMOTION_BUTTON_TEXTURE_ID,
    START_GAME_BUTTON_TEXTURE_ID,
    CONTINUE_GAME_BUTTON_TEXTURE_ID,
    EXIT_GAME_BUTTON_TEXTURE_ID,
    QUIT_GAME_BUTTON_TEXTURE_ID,
    START_SCREEN_TEXTURE_ID
} TextureIds;

/*Unique ID enum for all the font we use
Since size cannot be changed we encorporate the 
size of the font in the enum value*/
typedef enum {
    SERIFNCB_20_FONT_ID,    //SERIFCNB font with size 20
    SERIFNCB_50_FONT_ID,    //SERIFCNB font with size 50
    SERIFNCB_70_FONT_ID     //SERIFCNB font with size 70
} FontIds;

#endif /* INCLUDE_COMMON_COMMONDEFINES_H_ */