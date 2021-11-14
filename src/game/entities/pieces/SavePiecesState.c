/*      Own include     */
#include "game/entities/pieces/SavePiecesState.h"

/*    System includes   */
#include <stdio.h>
#include <string.h>

/* Third party includes */

/* Own library includes */
#include "utils/path/PathConfigurator.h"
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
    char filePath[50];
    configurePath(fileName, filePath);

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
    char* fileName = "savedGame.txt";
    char filePath[50];    
    configurePath(fileName, filePath);

    if ((fp = fopen(filePath, "w")) == NULL) {
        LOGERR("Error, did not load file: %s", filePath);
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