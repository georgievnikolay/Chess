/*      Own include     */
#include "game/utils/SaveFile.h"

/*    System includes   */
#include <stdio.h>
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "utils/ErrorCodes.h"
#include "utils/Log.h"

/* Forward declarations */

/*        Defines       */

/*
Capital letters are Whites and 
lower letters are Blacks

KING -> K or k
QUEEN -> Q or q
PAWN -> P or p
KNIGHT -> N or n
ROOK -> R or r
BISHOP -> B of b
NONE -> .

SEPARATOR -> /

*/

#define NO_PIECE '.'
#define SEPARATOR '\n'

char* map = "KQBNRPkqbnrp";

int32_t loadFile(PieceType outPieces[TILES_IN_ROW][TILES_IN_COL],
                 int32_t playerIds[TILES_IN_ROW][TILES_IN_COL], const char* fileName) {
    
    FILE* fp = NULL;
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

    char nextChar;
    int32_t charIdx;
    for (int32_t row = 0; row < TILES_IN_ROW; row++) {
        for(int32_t col = 0; col < TILES_IN_COL; col++) {
            nextChar = fgetc(fp);
            if (SEPARATOR == nextChar) {
                nextChar = fgetc(fp);
            }

            if (nextChar == EOF) {
                return FAILURE;
            }

            if (NO_PIECE == nextChar) {
                outPieces[row][col] = NONE;
                continue;
            }
            
            charIdx = 0;
            while (map[charIdx] != nextChar) {
                charIdx++;
            }

            playerIds[row][col] = charIdx / PIECE_TYPE_COUNT;
            outPieces[row][col] = charIdx % PIECE_TYPE_COUNT;
        }
    }

    fclose(fp);
    fp = NULL;

    return SUCCESS;
}

int32_t saveFile(const PieceType allPieces[TILES_IN_ROW][TILES_IN_COL],
                 int32_t playerIds[TILES_IN_ROW][TILES_IN_COL]) {
    FILE* fp = NULL;
    
    const char* fileName = NULL;
#ifdef RELEASE_BUILD
    fileName = "resources/gameFiles/savedGame.txt";
#else
    fileName = "../resources/gameFiles/savedGame.txt";
#endif

    if ((fp = fopen(fileName, "w")) == NULL) {
        LOGERR("Error, did not load file: %s", fileName);
        return FAILURE;
    }

    PieceType currPiece = 0;
    int32_t currPlayer = 0;
    char c;

    for (int32_t row = 0; row < TILES_IN_ROW; row++) {
        for(int32_t col = 0; col < TILES_IN_COL; col++) {
            currPiece = allPieces[row][col];
            currPlayer = playerIds[row][col];

            if (currPiece == NONE) {
                c = NO_PIECE;
            } else {
                c = map[currPiece + PIECE_TYPE_COUNT*currPlayer];                 
            }

            fputc(c, fp);
        }
        fputc(SEPARATOR, fp);
    }

    fclose(fp);
    fp = NULL;
    
    return SUCCESS;
}