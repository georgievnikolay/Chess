/*      Own include     */
#include "game/logic/GameLogic.h"

/*    System includes   */
#include <stdio.h>
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "game/config/GameLogicCfg.h"
#include "utils/drawing/Color.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

static void updateTimerText(struct Text* timerText, int32_t minutes, int32_t seconds) {
    char buffer[20];

    snprintf(buffer, 20, "%02d : %02d", minutes, seconds);
    setText(timerText, buffer);
}

static void onTimerTimeout(void* clientProxy, int32_t timerId) {
    struct GameLogic* self = (struct GameLogic*)clientProxy;

    int32_t minutes = self->timeUnits[MINUTES];
    int32_t seconds = self->timeUnits[SECONDS];
    LOGY("%02d : %02d", self->timeUnits[MINUTES], self->timeUnits[SECONDS])

    if (timerId == ONE_MINUTE_TIMER) {
        minutes = 1;
        seconds = 0;
        updateTimerText(&self->gameLogicTexts[TIMER_TEXT], minutes, seconds);
        return;
    } else if (timerId == ONE_SECOND_TIMER) {
        minutes = 0;
        if (seconds == 0) {
            seconds = 59;
        } else {
            seconds -= 1;
        }
        updateTimerText(&self->gameLogicTexts[TIMER_TEXT], minutes, seconds);
    } else {
        LOGERR("Error, recieved unsupported timerId");
    }

    self->timeUnits[MINUTES] = minutes;
    self->timeUnits[SECONDS] = seconds;  
}

int32_t initGameLogic(struct GameLogic* self, const struct GameLogicCfg* cfg) {
    
    createText(&self->gameLogicTexts[TIMER_TEXT], "NULL", cfg->fontId, &COLOR_BLACK, &POINT_UNDEFINED);
    int32_t textWidth = self->gameLogicTexts[TIMER_TEXT].widget.drawParams.width;

    int32_t startX = cfg->gameBoardWidth_Height + 
                (((cfg->screenWidth - cfg->gameBoardWidth_Height) - textWidth )/ 2);
    int32_t startY = cfg->screenHeight - 100;

    struct Point pos = { .x = startX, .y = startY};
    self->gameLogicTexts[TIMER_TEXT].widget.drawParams.pos = pos;

    pos.y -= 100;
    createText(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT], "WHITES", cfg->fontId, &COLOR_BLACK, &pos);

    self->timeUnits[MINUTES] = 1;
    self->timeUnits[SECONDS] = 0;
    self->activePlayerId = WHITE_PLAYER_ID;
    
    createTimer(&self->timerClent[ONE_MINUTE_TIMER], self, onTimerTimeout);
    createTimer(&self->timerClent[ONE_SECOND_TIMER], self, onTimerTimeout);
    
    return SUCCESS;
}

void deinitGameLogic(struct GameLogic* self) {
    destroyText(&self->gameLogicTexts[TIMER_TEXT]);
    destroyText(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT]);

    stopTimer(ONE_MINUTE_TIMER);
    stopTimer(ONE_SECOND_TIMER);
}

void drawGameLogic(struct GameLogic* self) {
    drawText(&self->gameLogicTexts[TIMER_TEXT]);
    drawText(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT]);
}

void finishTurn(struct GameLogic* self) {
    if (self->activePlayerId == WHITE_PLAYER_ID) {
        self->activePlayerId = BLACK_PLAYER_ID;
        setText(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT], "BLACKS");
    } else {
        self->activePlayerId = WHITE_PLAYER_ID;
        setText(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT], "WHITES");
    }
}

void startGameLogic(struct GameLogic* self) {

    int64_t oneMinuteInMiliseconds = 60000;
    int64_t oneSecondInMiliseconds = 1000;

    startTimer(&self->timerClent[ONE_MINUTE_TIMER], 
        oneMinuteInMiliseconds, ONE_MINUTE_TIMER, PULSE_TIMER);

    startTimer(&self->timerClent[ONE_SECOND_TIMER], 
        oneSecondInMiliseconds, ONE_SECOND_TIMER, PULSE_TIMER);
}

void stopGameLogic(struct GameLogic* self) {
    UNUSED(self);
    stopTimer(ONE_MINUTE_TIMER);
    stopTimer(ONE_SECOND_TIMER);
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