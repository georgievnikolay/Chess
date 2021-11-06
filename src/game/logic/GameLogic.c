/*      Own include     */
#include "game/logic/GameLogic.h"

/*    System includes   */
#include <stdio.h>
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

int32_t initGameLogic(struct GameLogic* self) {
    self->activePlayerId = WHITE_PLAYER_ID;
    return SUCCESS;
}

void finishTurn(struct GameLogic* self) {
    if (self->activePlayerId == WHITE_PLAYER_ID) {
        self->activePlayerId = BLACK_PLAYER_ID;
    } else {
        self->activePlayerId = WHITE_PLAYER_ID;
    }
}

int32_t loadGameLogic(struct GameLogic* gameLogic, char* fileName) {

    FILE* fp;

    char* back = "../";
    char* folder = "resources/";
    char filePath[50];
#ifdef RELEASE_BUILD
    strcpy(filePath, folder);
    strcat(filePath, fileName);
#else
    strcpy(filePath, back);
    strcat(filePath, folder);
    strcat(filePath, fileName);
#endif

    if ((fp = fopen(filePath, "r")) == NULL) {
        LOGERR("Error, did not load file: %s", filePath);
        return FAILURE;
    }

    char c;
    c = fgetc(fp);

    int32_t activePlayer = c - '0';
    gameLogic->activePlayerId = activePlayer;

    fclose(fp);
    fp = NULL;

    return SUCCESS;
}

int32_t saveGameLogic(const struct GameLogic* gameLogic) {

    FILE* fp;
    const char* filePath = NULL;
#ifdef RELEASE_BUILD
    filePath = "resources/savedGameLogic.txt";
#else
    filePath = "../resources/savedGameLogic.txt";
#endif

    if ((fp = fopen(filePath, "w")) == NULL) {
        LOGERR("Error, did not load file: %s", filePath);
        return FAILURE;
    }

    int32_t playerId = gameLogic->activePlayerId + '0';
    fputc(playerId, fp);

    fclose(fp);
    fp = NULL;    

    return SUCCESS;
}