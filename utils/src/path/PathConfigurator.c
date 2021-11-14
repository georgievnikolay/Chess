/*      Own include     */
#include "utils/path/PathConfigurator.h"

/*    System includes   */
#include <stdint.h>
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "utils/ErrorCodes.h"

/* Forward declarations */

/*        Defines       */

static void replaceCharacter(char* path) {
    int32_t len = strlen(path);

    for (int32_t i = 0; i < len; i++) {
        if (path[i] == LINUX_MAC_DIR_CHAR) {
            path[i] = WIN_DIR_CHAR;
        }
    }
}

void configureOSPath(char* path) {
#ifdef _WIN32
    replaceCharacter(path)
#else
    UNUSED(replaceCharacter(path));
#endif
}

void configurePath(const char* fileName, char* filePath) {
    char* folder = "resources/gameFiles/";
#ifdef RELEASE_BUILD
    strcpy(filePath, folder);
    strcat(filePath, fileName);
#else
    char* back = "../";
    strcpy(filePath, back);
    strcat(filePath, folder);
    strcat(filePath, fileName);
#endif
    configureOSPath(filePath);   
}