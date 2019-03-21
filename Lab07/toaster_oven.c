//Kameron Gill
//kgill2@ucsc.edu


//toaster_oven.h


// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"
#include "Adc.h"
#include "Buttons.h"
#include "Oled.h"
#include "Leds.h"
#include "Ascii.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>



// **** Set any macros or preprocessor directives here ****
// Set a macro for resetting the timers, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)
#define LONG_PRESS 5

// **** Declare any datatypes here ****
void UpdateMyOled(void);

typedef struct {
    int cookTimeLeft;
    int initTime;
    int temp;
    int cookMode;
    int buttonPressCounter;
    int inputSelection;
    int ovenState;
    int cookTimerFlag;
    uint8_t bEvent;
    uint16_t freeRunningCounter;
} OvenStateData;

enum {
    RESET,
    start,
    countDown,
    pendingSelectorChange,
    pendingRest,

} state = RESET;

// **** Define any module-level, global, or external variables here ****
static OvenStateData ovenData;
const char topOvenOn = 0x01; 
const char topOvenOff = 0x02;
const char bottomOvenOn = 0x03;
const char bottomOvenOff = 0x04;
static char result[200]; //char for printing stuff
static int cookTimerFlag; // 2hz timer
static int adcVal; 
static int adcVal1; 
static int adcVal2;
static int ledtime; // for countDown of leds





// Configuration Bit settings

int main()
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. We configure it using a 1:256 prescalar, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR1 to F_PB / 256 / 2 yields a 0.5s timer.
    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_256, BOARD_GetPBClock() / 256 / 2);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T1);
    INTSetVectorPriority(INT_TIMER_1_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_1_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T1, INT_ENABLED);

    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_16, BOARD_GetPBClock() / 16 / 100);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T2);
    INTSetVectorPriority(INT_TIMER_2_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_2_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T2, INT_ENABLED);

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescalar, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.
    OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_256, BOARD_GetPBClock() / 256 / 5);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T3);
    INTSetVectorPriority(INT_TIMER_3_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_3_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T3, INT_ENABLED);

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/

    OledInit();
    AdcInit();
    LEDS_INIT();
    ButtonsInit();
    ovenData.cookMode = 1;


    while (1) {
        adcVal2 = AdcRead(); // read one adc value

        OledClear(OLED_COLOR_BLACK); // clear screen
        UpdateMyOled();
         char test = 'x';




        switch (state) {
        case RESET:
            LEDS_SET(0x0); 
            ovenData.initTime = 1; 
            ovenData.inputSelection = 0; 
            ovenData.temp = 300; 
            ovenData.cookMode = ovenData.cookMode; 
            ovenData.ovenState = 0; // 0 = oven off
            state = start;
            UpdateMyOled();
            break;

        case start:
            adcVal1 = AdcRead(); // read second value from adc

            if (adcVal1 != adcVal2) { 
                if (ovenData.inputSelection == 0) {
                    adcVal = AdcRead();
                    ovenData.initTime = (adcVal >> 2) + 1;
                    UpdateMyOled();
                    state = start;
                } else if (ovenData.inputSelection == 1) { 
                    adcVal = AdcRead();
                    ovenData.temp = (adcVal >> 2) + 300;
                    UpdateMyOled();
                    state = start;
                }
            } else if (!(ovenData.bEvent & BUTTON_EVENT_4DOWN) == 0) {
                LEDS_SET(0xFF); // start cooking
                cookTimerFlag = 0;
                ovenData.cookTimeLeft = ovenData.initTime;
                ovenData.ovenState = 1; // turn oven on
                ovenData.bEvent = 0; // clear button event
                UpdateMyOled();
                state = countDown;
            } else if (!(ovenData.bEvent & BUTTON_EVENT_3DOWN) == 0) {
                ovenData.buttonPressCounter = ovenData.freeRunningCounter; 
                ovenData.bEvent = 0; // clear button event
                state = pendingSelectorChange;
            }
            break;

        case countDown:
            if (ovenData.cookTimerFlag == 1 && !(ovenData.cookTimeLeft < 0)) {
                ovenData.cookTimeLeft--; // decrement timer
                ovenData.cookTimerFlag = 0;
                ledtime = (ovenData.initTime * 7) / 8; // LED countDown code below based on time value
                if (!(ovenData.cookTimeLeft != ledtime)) {
                    LEDS_SET(0xFE);
                }
                ledtime = (ovenData.initTime * 6) / 8;
                if (!(ovenData.cookTimeLeft != ledtime)) {
                    LEDS_SET(0xFC);
                }
                ledtime = (ovenData.initTime * 5) / 8;
                if (!(ovenData.cookTimeLeft != ledtime)) {
                    LEDS_SET(0xF8);
                }
                ledtime = (ovenData.initTime * 4) / 8;
                if (!(ovenData.cookTimeLeft != ledtime)) {
                    LEDS_SET(0xF << 4);
                }
                ledtime = (ovenData.initTime * 3) / 8;
                if (!(ovenData.cookTimeLeft != ledtime)) {
                    LEDS_SET(0xE << 4);
                }
                ledtime = (ovenData.initTime * 2) / 8;
                if (!(ovenData.cookTimeLeft != ledtime)) {
                    LEDS_SET(0xC << 4);
                }
                ledtime = (ovenData.initTime * 1) / 8;
                if (!(ovenData.cookTimeLeft != ledtime)) {
                    LEDS_SET(0x80);
                }
                UpdateMyOled();
                state = countDown;
            } else if (ovenData.bEvent & BUTTON_EVENT_4DOWN) {
                ovenData.buttonPressCounter = ovenData.freeRunningCounter;
                ovenData.bEvent = 0;
                state = pendingRest;
            } else if (!(ovenData.cookTimerFlag == 0) && !(ovenData.cookTimeLeft == 1)) {
                UpdateMyOled();
                state = RESET;
                ovenData.cookTimerFlag = 0;
            }
            break;

        case pendingSelectorChange:

            if (!(ovenData.freeRunningCounter - ovenData.buttonPressCounter > LONG_PRESS)) {

                if (ovenData.bEvent & BUTTON_EVENT_3UP) {
                    ovenData.initTime = 0;
                    ovenData.temp = 300;
                    ovenData.inputSelection = 0; 
                    if (ovenData.cookMode == 1 || 2) {
                        ovenData.cookMode++; 
                    }
                    if (ovenData.cookMode == 4) { 
                        ovenData.cookMode = 1;
                    }
                    UpdateMyOled();
                    ovenData.bEvent = 0; // clear button event
                    state = start;
                }
            }
            if (!(ovenData.freeRunningCounter - ovenData.buttonPressCounter < LONG_PRESS)) {
                if (!(ovenData.inputSelection = !1)) { 
                    ovenData.inputSelection = 0;
                } else {
                    ovenData.inputSelection = 1; 
                }
                ovenData.temp = (adcVal >> 2) + 300; 

                ovenData.initTime = (adcVal >> 2) + 1;
                UpdateMyOled();
                ovenData.bEvent = 0;
                state = start;

            }
            break;

        case pendingRest:
           
            if (ovenData.cookTimerFlag == 1 && ovenData.cookTimeLeft > 0) {
                test = 'a';
            } else if (ovenData.bEvent & BUTTON_EVENT_4UP) {
                test = 'b';
            } else if (ovenData.freeRunningCounter - ovenData.buttonPressCounter >= LONG_PRESS) {
                test = 'c';
            } else if (ovenData.cookTimerFlag == 1 && ovenData.cookTimeLeft == 0) {
                test = 'd';
            }

            switch (test) {
            case 'a':
                ovenData.cookTimeLeft--;
                UpdateMyOled();
                ovenData.cookTimerFlag = 0;
                state = pendingRest;
                break;
            case 'b':
                ovenData.bEvent = 0;
                state = countDown;
                break;
            case 'c':
                state = RESET;
                break;
            case 'd':
                ovenData.cookTimerFlag = 0;
                state = RESET;
                break;




            }
            break;
        }










        }





        /***************************************************************************************************
         * Your code goes in between this comment and the preceding one with asterisks
         **************************************************************************************************/
        while (1);
    }

    //the following updates the OLED screen

    void UpdateMyOled(void)
    {
        //OledClear(OLED_COLOR_BLACK); // clear screen
        char x;

        //checks to see what state oven is in to know what to print

        if (ovenData.cookMode == 1 && ovenData.ovenState == 1) {
            x = 'a';
        } else if (ovenData.cookMode == 1 && ovenData.ovenState == 0 && ovenData.inputSelection == 0)
            x = 'b';
        else if (ovenData.cookMode == 1 && ovenData.ovenState == 0 && ovenData.inputSelection == 1)
            x = 'c';
        else if (ovenData.cookMode == 2 && ovenData.ovenState == 0)
            x = 'd';
        else if (ovenData.cookMode == 2 && ovenData.ovenState == 1)
            x = 'e';
        else if (ovenData.cookMode == 3 && ovenData.ovenState == 0)
            x = 'f';
        else if (ovenData.cookMode == 3 && ovenData.ovenState == 1)
            x = 'g';

        switch (x) {
        case 'a':
            sprintf(result, "%c%c%c%c%c%c%15s%s%s%5s%11s%d%s%d%s%s%5s%11s%d%c%c%c%c%c%c%c", topOvenOn, topOvenOn, topOvenOn, topOvenOn, topOvenOn, topOvenOn, "Mode: Bake", "\n", "|", "|", "Time: ", ovenData.cookTimeLeft / 60, ":", ovenData.cookTimeLeft % 60, "\n", "|", "|", "Temp: ", ovenData.temp, 0xF8, bottomOvenOn, bottomOvenOn, bottomOvenOn, bottomOvenOn, bottomOvenOn, bottomOvenOn);
            OledDrawString(result);
            OledUpdate();
            break;
        case 'b':
            sprintf(result, "%c%c%c%c%c%c%15s%s%s%5s%11s%d%s%d%s%s%5s%11s%d%c%c%c%c%c%c%c", topOvenOff, topOvenOff, topOvenOff, topOvenOff, topOvenOff, topOvenOff, "Mode: Bake", "\n", "|", "|", "> Time: ", ovenData.initTime / 60, ":", ovenData.initTime % 60, "\n", "|", "|", "Temp: ", ovenData.temp, 0xF8, bottomOvenOff, bottomOvenOff, bottomOvenOff, bottomOvenOff, bottomOvenOff, bottomOvenOff);
            OledDrawString(result);
            OledUpdate();
            break;
        case 'c':
            sprintf(result, "%c%c%c%c%c%c%15s%s%s%5s%11s%d%s%d%s%s%5s%11s%d%c%c%c%c%c%c%c", topOvenOff, topOvenOff, topOvenOff, topOvenOff, topOvenOff, topOvenOff, "Mode: Bake", "\n", "|", "|", "Time: ", ovenData.initTime / 60, ":", ovenData.initTime % 60, "\n", "|", "|", "> Temp: ", ovenData.temp, 0xF8, bottomOvenOff, bottomOvenOff, bottomOvenOff, bottomOvenOff, bottomOvenOff, bottomOvenOff);
            OledDrawString(result);
            OledUpdate();
            break;
        case 'd':
            sprintf(result, "%c%c%c%c%c%c%15s%s%s%5s%10s%d%s%d%s%c%c%c%c%c%c", topOvenOff, topOvenOff, topOvenOff, topOvenOff, topOvenOff, topOvenOff, "Mode: Toast", "\n", "|", "|", "Time: ", ovenData.initTime / 60, ":", ovenData.initTime % 60, "\n", bottomOvenOff, bottomOvenOff, bottomOvenOff, bottomOvenOff, bottomOvenOff, bottomOvenOff);
            OledDrawString(result);
            OledUpdate();
            break;
        case 'e':
            sprintf(result, "%c%c%c%c%c%c%15s%s%s%5s%10s%d%s%d%s%c%c%c%c%c%c", topOvenOff, topOvenOff, topOvenOff, topOvenOff, topOvenOff, topOvenOff, "Mode: Toast", "\n", "|", "|", "Time: ", ovenData.cookTimeLeft / 60, ":", ovenData.cookTimeLeft % 60, "\n", bottomOvenOn, bottomOvenOn, bottomOvenOn, bottomOvenOn, bottomOvenOn, bottomOvenOn);
            OledDrawString(result);
            OledUpdate();
            break;
        case 'f':
            sprintf(result, "%c%c%c%c%c%c%15s%s%s%5s%11s%d%s%d%s%s%5s%14s%c%s%c%c%c%c%c%c", topOvenOff, topOvenOff, topOvenOff, topOvenOff, topOvenOff, topOvenOff, "Mode:Broil", "\n", "|", "|", "Time: ", ovenData.initTime / 60, ":", ovenData.initTime % 60, "\n", "|", "|", "Temp: 500", 0xF8, "\n", bottomOvenOff, bottomOvenOff, bottomOvenOff, bottomOvenOff, bottomOvenOff, bottomOvenOff);
            OledDrawString(result);
            OledUpdate();
            break;
        case 'g':
            sprintf(result, "%c%c%c%c%c%c%15s%s%s%5s%11s%d%s%d%s%s%5s%14s%c%s%c%c%c%c%c%c", topOvenOn, topOvenOn, topOvenOn, topOvenOn, topOvenOn, topOvenOn, "Mode:Broil", "\n", "|", "|", "Time: ", ovenData.cookTimeLeft / 60, ":", ovenData.cookTimeLeft % 60, "\n", "|", "|", "Temp: 500", 0xF8, "\n", bottomOvenOff, bottomOvenOff, bottomOvenOff, bottomOvenOff, bottomOvenOff, bottomOvenOff);
            OledDrawString(result);
            OledUpdate();
            break;



        }
    }

    void __ISR(_TIMER_1_VECTOR, ipl4auto) TimerInterrupt2Hz(void)
    {

        // Clear the interrupt flag.
        IFS0CLR = 1 << 4;


        ovenData.cookTimerFlag = TRUE;

    }

    void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void)
    {
        // Clear the interrupt flag.
        IFS0CLR = 1 << 12;

        ovenData.freeRunningCounter++;

    }

    void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
    {
        // Clear the interrupt flag.
        IFS0CLR = 1 << 8;

        ovenData.bEvent = ButtonsCheckEvents();

    }