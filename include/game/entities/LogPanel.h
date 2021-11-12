#ifndef INCLUDE_GAME_ENTITIES_LOGPANEL_H_
#define INCLUDE_GAME_ENTITIES_LOGPANEL_H_

/*      Own include     */

/*    System includes   */
#include <stdint.h>

/* Third party includes */

/* Own library includes */
#include "game/defines/ChessDefines.h"
#include "game/config/LogPanelCfg.h"
#include "manager_utils/drawing/Text.h"

/* Forward declarations */
struct BoardPos;
struct ChessPiece;

/*        Defines       */

enum LogPanelDefines {
    MAX_LOGS = 10
};

struct LogPanel {
    struct Text moveLogs[MAX_LOGS];
    struct LogPanelCfg cfg;
    int32_t size;
};

int32_t initLogPanel(struct LogPanel* self, const struct LogPanelCfg* cfg, char* fileName);

void drawLogPanel(struct LogPanel* self);

void addNewLog(struct LogPanel* self, const struct ChessPiece* movedPiece);

void deinitLogPanel(struct LogPanel* self);

int32_t loadLogPanel(struct LogPanel* self, const char* fileName);

int32_t saveLogPanel(struct LogPanel* self);

#endif /* INCLUDE_GAME_ENTITIES_LOGPANEL_H_ */