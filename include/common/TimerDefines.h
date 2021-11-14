#ifndef INCLUDE_COMMON_TIMERDEFINES_H_
#define INCLUDE_COMMON_TIMERDEFINES_H_

/*      Own include     */

/*    System includes   */

/* Third party includes */

/* Own library includes */

/* Forward declarations */

/*        Defines       */

/*Unique IDs for all the different timers 
our application is goint to use*/
typedef enum {
    GAMELOGIC_ONE_SECOND_TIMER,     //Timer for player turns cap
    PIECE_HANDLER_HELPER_TIMER      //Timer for check and Checkmate texts
} TimerIds;

#endif /* INCLUDE_COMMON_TIMERDEFINES_H_ */