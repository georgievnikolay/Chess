#ifndef UTILS_INCLUDE_UTILS_PATH_PATHCONFIGURATOR_H_
#define UTILS_INCLUDE_UTILS_PATH_PATHCONFIGURATOR_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */

/* Forward declarations */

/*        Defines       */

#define WIN_DIR_CHAR '/'
#define LINUX_MAC_DIR_CHAR '\\'

void configureOSPath(char* path);

void configurePath(const char* fileName, char* filePath);

#endif /* UTILS_INCLUDE_UTILS_PATH_PATHCONFIGURATOR_H_ */