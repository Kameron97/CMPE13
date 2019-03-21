//kameron Gill
//kgill2@ucsc.edu

// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"
#include "Leds.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries

// **** Set macros and preprocessor directives ****
#define LEFT 1
#define RIGHT 0

// **** Declare any datatypes here ****
struct TimerResult {
    uint8_t event;
    uint8_t value;
};
// **** Define global, module-level, or external variables here ****
static struct TimerResult time;

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_8, 0xFFFF);

    // Set up the timer interrupt with a priority of 4.
    INTClearFlag(INT_T1);
    INTSetVectorPriority(INT_TIMER_1_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_1_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T1, INT_ENABLED);

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
 LEDS_INIT();
 LEDS_SET(0x01); //set LED to 1
 int direction = RIGHT;

 while(1){
    //checks to see if event is true
    if (time.event == 1){
        //checks to see if LED is on the end LED
        if (LEDS_GET() == 0x01)
            //if so go left
            direction = LEFT;
            //chek to see if led is on first spot
         if (LEDS_GET() == 0x80)
            direction = RIGHT;

         if (direction == 1)
                LEDS_SET(LEDS_GET() << 1);

          if (direction == 0)
                LEDS_SET(LEDS_GET() >> 1);

            time.event = 0;
        }
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. During each call it increments a counter (the
 * value member of a module-level TimerResult struct). This counter is then checked against the
 * binary values of the four switches on the I/O Shield (where SW1 has a value of 1, SW2 has a value
 * of 2, etc.). If the current counter is greater than this switch value, then the event member of a
 * module-level TimerResult struct is set to true and the value member is cleared.
 */
void __ISR(_TIMER_1_VECTOR, IPL4AUTO) Timer1Handler(void)
{
    // Clear the interrupt flag.
      time.value++;

    INTClearFlag(INT_T1);
    if (time.value > SWITCH_STATES()) {
        time.event = 1;
        time.value = 0;
    }


}