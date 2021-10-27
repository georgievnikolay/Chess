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

#endif /* INCLUDE_GAME_DEFINES_CHESSDEFINES_H_ */