/*      Own include     */
#include "game/logic/GameLogic.h"

/*    System includes   */
#include <stdio.h>
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "game/proxies/GameProxy.h"
#include "game/defines/ChessDefines.h"
#include "game/config/GameLogicCfg.h"
#include "utils/drawing/Color.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

static void updateTimerTextColor(struct Text* timerText, int32_t timeUnits[TIME_UNITS_COUNT]) {
    if (11 >= timeUnits[SECONDS] && timeUnits[SECONDS] >= 0) {
        setColorText(timerText, &COLOR_RED);
        return;
    } else if (21 >= timeUnits[SECONDS] && timeUnits[SECONDS] >= 11) {
        setColorText(timerText, &COLOR_ORANGE);
        return;
    } else {
        setColorText(timerText, &COLOR_BLACK);
    }
}

static void updateTimerText(struct Text* timerText, int32_t timeUnits[TIME_UNITS_COUNT]) {
    char buffer[20];

    snprintf(buffer, 20, "%02d:%02d", timeUnits[MINUTES], timeUnits[SECONDS]);
    setText(timerText, buffer);
}

static void onTimerTimeout(void* clientProxy, int32_t timerId) {
    struct GameLogic* self = (struct GameLogic*)clientProxy;

    // LOGY("%02d : %02d", self->timeUnits[MINUTES], self->timeUnits[SECONDS])
    // setColorText(&self->gameLogicTexts[TIMER_TEXT], &COLOR_RED);
    updateTimerTextColor(&self->gameLogicTexts[TIMER_TEXT], self->timeUnits);
    if (timerId == ONE_SECOND_TIMER) {
        self->timeUnits[SECONDS] -= 1;
            
        if (self->timeUnits[SECONDS] < 0) {
            self->timeUnits[MINUTES] = 1;
            self->timeUnits[SECONDS] = 0;
            updateTimerText(&self->gameLogicTexts[TIMER_TEXT], self->timeUnits);
            finishTurnGameProxy(self->gameProxy);
        } else {
            updateTimerText(&self->gameLogicTexts[TIMER_TEXT], self->timeUnits);
        }
    }
}

int32_t initGameLogic(struct GameLogic* self, const struct GameLogicCfg* cfg, void* gameProxy) {
    
    if (NULL == gameProxy) {
        LOGERR("Error, NULL provided for gameProxy");
        return FAILURE;
    }
    self->gameProxy = gameProxy;

    self->timeUnits[MINUTES] = 0;
    self->timeUnits[SECONDS] = 60;
    self->activePlayerId = WHITE_PLAYER_ID;
    self->numberOfMoves = 0;

    createTimer(&self->timerClent[ONE_SECOND_TIMER], self, onTimerTimeout);

    createText(&self->gameLogicTexts[TIMER_TEXT], "01:00", cfg->fontId, &COLOR_BLACK, &POINT_UNDEFINED);
    int32_t textWidth = self->gameLogicTexts[TIMER_TEXT].widget.drawParams.width;

    int32_t startX = cfg->gameBoardWidth_Height + 
                (((cfg->screenWidth - cfg->gameBoardWidth_Height) - textWidth )/ 2);
    int32_t startY = cfg->screenHeight - 100;

    struct Point pos = { .x = startX, .y = startY};
    self->gameLogicTexts[TIMER_TEXT].widget.drawParams.pos = pos;

    pos.y -= 100;
    createText(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT], "WHITES", cfg->fontId, &COLOR_BLACK, &pos);
    
    return SUCCESS;
}

void deinitGameLogic(struct GameLogic* self) {
    destroyText(&self->gameLogicTexts[TIMER_TEXT]);
    destroyText(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT]);

    if (isActiveTimerId(ONE_SECOND_TIMER)) {
        stopTimer(ONE_SECOND_TIMER);
    }
}

void drawGameLogic(struct GameLogic* self) {
    drawText(&self->gameLogicTexts[TIMER_TEXT]);
    drawText(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT]);
}

void finishTurn(struct GameLogic* self) {
    self->timeUnits[MINUTES] = 0;
    self->timeUnits[SECONDS] = 60;

    if (self->activePlayerId == WHITE_PLAYER_ID) {
        self->activePlayerId = BLACK_PLAYER_ID;
        setText(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT], "BLACKS");
    } else {
        self->activePlayerId = WHITE_PLAYER_ID;
        setText(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT], "WHITES");
    }
}

void startGameLogic(struct GameLogic* self) {

    int64_t oneSecondInMiliseconds = 1000;

    startTimer(&self->timerClent[ONE_SECOND_TIMER], 
        oneSecondInMiliseconds, ONE_SECOND_TIMER, PULSE_TIMER);

    self->timeUnits[MINUTES] = 0;
    self->timeUnits[SECONDS] = 60;
}

void stopGameLogic(struct GameLogic* self) {
    UNUSED(self);
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

    fscanf(fp, "%d/%d/%d/%d", &gameLogic->activePlayerId, 
                              &gameLogic->numberOfMoves, 
                              &gameLogic->timeUnits[MINUTES], 
                              &gameLogic->timeUnits[SECONDS]);

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

    fprintf(fp, "%d/%d/%d/%d", gameLogic->activePlayerId, 
                               gameLogic->numberOfMoves, 
                               gameLogic->timeUnits[MINUTES], 
                               gameLogic->timeUnits[SECONDS]);

    fclose(fp);
    fp = NULL;    

    return SUCCESS;
}