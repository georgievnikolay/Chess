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

static const char* whitePlayerText = "WHITES";
static const char* blackPlayerText = "BLACKS";

static const char* initialTimerText = "01:00";

#define TIMER_FORMAT "%02d:%02d"

/* BEGIN Text utility functions specific for GameLogic */
static void updateTimerTextColor(struct Text* timerText, int32_t seconds) {
    if (11 >= seconds && seconds >= 0) {
        setColorText(timerText, &COLOR_RED);
        return;
    } else if (21 >= seconds && seconds >= 11) {
        setColorText(timerText, &COLOR_ORANGE);
        return;
    } else {
        setColorText(timerText, &COLOR_BLACK);
    }
}

static void updateTimerText(struct Text* timerText, int32_t seconds) {
    char buffer[20];
    int32_t minute = seconds / 60;
    seconds = seconds % 60;

    snprintf(buffer, 20, TIMER_FORMAT, minute, seconds);
    setText(timerText, buffer);
}

static void centreTextXAxis(struct Text* text, const struct GameLogicCfg* cfg ) {
    int32_t textWidth = text->widget.drawParams.width;

    int32_t startX = cfg->gameBoardWidth_Height + 
                (((cfg->screenWidth - cfg->gameBoardWidth_Height) - textWidth )/ 2);
    int32_t startY = cfg->screenHeight - 100;

    struct Point pos = { .x = startX, .y = startY};
    text->widget.drawParams.pos = pos;
}

static void moveTextYAxis(struct Text* text, int32_t offset) {
    text->widget.drawParams.pos.y += offset;
}
/* END  Text utility functions specific for GameLogic */

/* Timer callback */
static void onTimerTimeout(void* clientProxy, int32_t timerId) {
    struct GameLogic* self = (struct GameLogic*)clientProxy;

    updateTimerTextColor(&self->gameLogicTexts[TIMER_TEXT], self->turnSeconds);
    if (timerId == GAMELOGIC_ONE_SECOND_TIMER) {
        self->turnSeconds -= 1;
            
        updateTimerText(&self->gameLogicTexts[TIMER_TEXT], self->turnSeconds);
        
        if (self->turnSeconds == 0) {
            finishTurnGameProxy(self->gameProxy);
        }
    }
}

int32_t initGameLogic(struct GameLogic* self, const struct GameLogicCfg* cfg, void* gameProxy) {
    
    if (NULL == gameProxy) {
        LOGERR("Error, NULL provided for gameProxy");
        return FAILURE;
    }
    self->gameProxy = gameProxy;

    self->turnSeconds = 60;
    self->activePlayerId = WHITE_PLAYER_ID;
    self->numberOfMoves = 0;

    createTimer(&self->timerClent, self, onTimerTimeout);


    createText(&self->gameLogicTexts[TIMER_TEXT], initialTimerText, 
               cfg->fontId, &COLOR_BLACK, &POINT_UNDEFINED);
    centreTextXAxis(&self->gameLogicTexts[TIMER_TEXT], cfg);


    createText(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT], whitePlayerText, 
               cfg->fontId, &COLOR_BLACK, &POINT_UNDEFINED);
    centreTextXAxis(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT], cfg);
    moveTextYAxis(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT], -100);

    return SUCCESS;
}

void deinitGameLogic(struct GameLogic* self) {
    destroyText(&self->gameLogicTexts[TIMER_TEXT]);
    destroyText(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT]);

    if (isActiveTimerId(GAMELOGIC_ONE_SECOND_TIMER)) {
        stopTimer(GAMELOGIC_ONE_SECOND_TIMER);
    }
}

void drawGameLogic(struct GameLogic* self) {
    drawText(&self->gameLogicTexts[TIMER_TEXT]);
    drawText(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT]);
}

void finishTurn(struct GameLogic* self) {
    self->turnSeconds = 60;

    if (self->activePlayerId == WHITE_PLAYER_ID) {
        self->activePlayerId = BLACK_PLAYER_ID;
        setText(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT], blackPlayerText);
    } else {
        self->activePlayerId = WHITE_PLAYER_ID;
        setText(&self->gameLogicTexts[ACTIVE_PLAYER_TEXT], whitePlayerText);
    }
}

void startGameLogic(struct GameLogic* self) {
    int64_t oneSecondInMiliseconds = 1000;

    updateTimerText(&self->gameLogicTexts[TIMER_TEXT], self->turnSeconds);
    updateTimerTextColor(&self->gameLogicTexts[TIMER_TEXT], self->turnSeconds);
    
    startTimer(&self->timerClent, oneSecondInMiliseconds, 
               GAMELOGIC_ONE_SECOND_TIMER, PULSE_TIMER);
}

void stopGameLogic(struct GameLogic* self) {
    UNUSED(self);
    stopTimer(GAMELOGIC_ONE_SECOND_TIMER);
}

int32_t loadGameLogic(struct GameLogic* self, const char* fileName) {

    FILE* fp;

    char* back = "../";
    char* folder = "resources/gameFiles/";
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

    fscanf(fp, "%d/%d/%d", &self->activePlayerId, 
                           &self->numberOfMoves, 
                           &self->turnSeconds);

    fclose(fp);
    fp = NULL;

    return SUCCESS;
}

int32_t saveGameLogic(const struct GameLogic* self) {

    FILE* fp;
    const char* filePath = NULL;
#ifdef RELEASE_BUILD
    filePath = "resources/gameFiles/savedGameLogic.txt";
#else
    filePath = "../resources/gameFiles/savedGameLogic.txt";
#endif

    if ((fp = fopen(filePath, "w")) == NULL) {
        LOGERR("Error, did not load file: %s", filePath);
        return FAILURE;
    }

    fprintf(fp, "%d/%d/%d", self->activePlayerId, 
                            self->numberOfMoves, 
                            self->turnSeconds);

    fclose(fp);
    fp = NULL;    

    return SUCCESS;
}