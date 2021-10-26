#ifndef INCLUDE_COMMON_COMMONDEFINES_H_
#define INCLUDE_COMMON_COMMONDEFINES_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */

/* Forward declarations */

/*        Defines       */

typedef enum {
    RUNNING_GIRL_ID,
    WHEEL_ID,
    START_BUTTON_ID,
    STOP_BUTTON_ID
} TextureIds;

/*Unique ID enum for all the font we use
Since size cannot be changed we encorporate the 
size of the font in the enum value*/
typedef enum {
    ANGELINE_VINTAGE_40_FONT_ID,    //Angeline vintage font with size 40
    ANGELINE_VINTAGE_80_FONT_ID     //Angeline vintage font with size 80
} FontIds;

#endif /* INCLUDE_COMMON_COMMONDEFINES_H_ */