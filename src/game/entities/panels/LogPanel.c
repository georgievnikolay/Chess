/*      Own include     */
#include "game/entities/panels/LogPanel.h"

/*    System includes   */
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "game/entities/pieces/types/ChessPiece.h"
#include "utils/path/PathConfigurator.h"
#include "utils/drawing/Point.h"
#include "utils/drawing/Color.h"
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

static const char* NO_TEXT = "-";

static void translateBoardPos(const struct BoardPos* boardPos, 
                              int32_t playerId, char* buffer) {

    char localBuffer[15];
    int32_t row;
    int32_t col;

    if (playerId == WHITE_PLAYER_ID) {
        row = 8 - boardPos->row;
        col = boardPos->col + 'a';
    } else {
        row = boardPos->row + 1;
        col = 'h' - boardPos->col;
    }

    snprintf(localBuffer, 15, "%c%d", (char)col, row);
    strcat(buffer, localBuffer);
}

static void translatePieceType(const PieceType pieceType, char* buffer) {
    switch (pieceType) {
        case KING:
            strcat(buffer, "King on ");
            break;

        case QUEEN:
            strcat(buffer, "Queen on ");
            break;

        case BISHOP:
            strcat(buffer, "Bishop on ");
            break;

        case ROOK:
            strcat(buffer, "Rook on ");
            break;

        case PAWN:
            strcat(buffer, "Pawn on ");
            break;

        case KNIGHT:
            strcat(buffer, "Knight on ");
            break;

        default:
            LOGERR("Error wrong PieceType for translatePieceType");
            break;       
    }
}

static void translatePlayerId(int32_t playerId, char* buffer) {
    if (playerId == WHITE_PLAYER_ID) {
        strcat(buffer, "White ");
    } else {
        strcat(buffer, "Black ");
    }
}

static void translatePieceInformation(const struct BoardPos* boardPos, 
                                      const PieceType pieceType, 
                                      int32_t playerId, char* newLog) {
    translatePlayerId(playerId, newLog);
    translatePieceType(pieceType, newLog);
    translateBoardPos(boardPos, playerId, newLog);
}


static void setTextPosition(struct Text* text, int32_t offsetMultiplier, 
                            const struct LogPanelCfg* cfg) {
    int32_t offsetYInPixels = 35;
    int32_t firstTextPos = 200;

    int32_t startX = cfg->gameBoardWidth + 
                (((cfg->screenWidth - cfg->gameBoardWidth) - text->widget.drawParams.width) / 2);
    int32_t startY = firstTextPos + (offsetYInPixels * offsetMultiplier);

    text->widget.drawParams.pos.x = startX;
    text->widget.drawParams.pos.y = startY;
}

int32_t initLogPanel(struct LogPanel* self, const struct LogPanelCfg* cfg, const char* fileName) {
    
    self->cfg = *cfg;
    self->size = 0;

    for (int32_t i = 0; i < MAX_LOGS; i++) {
        resetText(&self->moveLogs[i]);
        createText(&self->moveLogs[i], NO_TEXT, cfg->fontId, &COLOR_BLACK, &POINT_UNDEFINED);
        setTextPosition(&self->moveLogs[i], i, cfg);
    }
    loadLogPanel(self, fileName);

    return SUCCESS;
}

void addNewLog(struct LogPanel* self, const struct ChessPiece* movedPiece) {
    char newLog[30] = "";
    char prevLog[30] = "";
    char currLog[30] = "";

    translatePieceInformation(&movedPiece->boardPos, movedPiece->pieceType, 
                              movedPiece->playerId, newLog);

    if (self->size < MAX_LOGS) {
        self->size++;
    }

    strcpy(prevLog, self->moveLogs[0].textContent);
    for (int32_t i = 1; i < self->size; i++) {
        strcpy(currLog, self->moveLogs[i].textContent);
        
        setText(&self->moveLogs[i], prevLog);
        setTextPosition(&self->moveLogs[i], i, &self->cfg);

        strcpy(prevLog, currLog);
    }

    setText(&self->moveLogs[0], newLog);
    setTextPosition(&self->moveLogs[0], 0, &self->cfg);
}

void drawLogPanel(struct LogPanel* self) {
    for (int32_t i = 0; i < self->size; i++) {
        drawText(&self->moveLogs[i]);
    }
}

void deinitLogPanel(struct LogPanel* self) {
    for (int32_t i = 0; i < MAX_LOGS; i++) {
        destroyText(&self->moveLogs[i]);
    }
    self->size = 0;
}

int32_t loadLogPanel(struct LogPanel* self, const char* fileName) {
    
    FILE* fp;
    
    char filePath[50];
    configurePath(fileName, filePath);

    if ((fp = fopen(filePath, "r")) == NULL) {
        LOGERR("Error, did not load file: %s", filePath);
        return FAILURE;
    }

    char line[30] = "";

    for (int32_t i = 0; i < MAX_LOGS; i++) {

        if (fgets(line, 30, fp) == NULL) {
            LOGERR("loadLogPanel() reached end of file earlier than expected");
            return FAILURE;
        }

        line[strlen(line) - 1] = '\0';

        setText(&self->moveLogs[i], line);
        setTextPosition(&self->moveLogs[i], i, &self->cfg);

        if (0 == (strcmp(NO_TEXT, line))) {
            continue;
        }
        self->size++;
    }

    fclose(fp);
    fp = NULL;

    return SUCCESS;    
}

int32_t saveLogPanel(struct LogPanel* self) {
    FILE* fp;
    
    char* fileName = "savedLogPanel.txt";
    char filePath[50];    
    configurePath(fileName, filePath);

    if ((fp = fopen(filePath, "w")) == NULL) {
        LOGERR("Error, did not load file: %s", filePath);
        return FAILURE;
    }

    for (int32_t i = 0; i < MAX_LOGS; i++) {
        fprintf(fp, "%s\n", self->moveLogs[i].textContent);
    }

    fclose(fp);
    fp = NULL;

    return SUCCESS;    
}
