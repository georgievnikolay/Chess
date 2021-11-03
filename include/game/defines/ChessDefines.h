#ifndef INCLUDE_GAME_DEFINES_CHESSDEFINES_H_
#define INCLUDE_GAME_DEFINES_CHESSDEFINES_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */

/* Forward declarations */

/*        Defines       */

enum PlayerId {
    WHITE_PLAYER_ID,
    BLACK_PLAYER_ID,

    PLAYERS_COUNT
};

typedef enum {
    KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN
} PieceType;

typedef enum {
    MOVE_TILE, GUARD_TILE, TAKE_TILE
} TileType;

typedef enum {
    UP_LEFT,
    UP,
    UP_RIGHT,
    RIGHT,
    DOWN_RIGHT,
    DOWN,
    DOWN_LEFT,
    LEFT,
    DIRECTION_COUNT
//TODO: KNIGHT define, not linear
} Direction;

enum PieceHandlerDefines {
    PLAYER_END_PAWN_ROW = 0,
    
    WHITE_PLAYER_START_PAWN_ROW = 6,
    BLACK_PLAYER_START_PAWN_ROW = 1,

    BOARD_ROWS_COLS = 7,
    STARTING_PIECES_COUNT = 16,
    TILES_IN_ROW = 8,
    TILES_IN_COL = 8,
    BOARD_MID = 4,
    NONE = -1
};

#endif /* INCLUDE_GAME_DEFINES_CHESSDEFINES_H_ */