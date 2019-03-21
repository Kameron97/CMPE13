//kameron Gill
//kgill2@ucsc.edu
//heap was 2056
// **** Include libraries here ****
// Standard C libraries
#include <string.h>


//CMPE13 Support Library
#include "BOARD.h"
#include "Ascii.h"
#include "Morse.h"
#include "Oled.h"
#include "OledDriver.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries


// **** Set any macros or preprocessor directives here ****
// Specify a bit mask for setting/clearing the pin corresponding to BTN4. Should only be used when
// unit testing the Morse event checker.
#define BUTTON4_STATE_FLAG (1 << 7)

// **** Declare any data types here ****
static MorseEvent eventMorse = 0;
#define BUTTON4_STATE_FLAG (1 << 7)

#define OLED_WIDTH 21 //Oled Width 21, Board.h Oled Width 21.33
#define STRING_EMPTY(x) sprintf(x,"%s",EMPTY) //Makes a line empty
#define EMPTY "                     " //21 characters of blank space
#define SPACE ' ' //1 character of balnk space
#define DISPLAY_WRITE() sprintf(display,"%s%s%s%s",topLine,secondLine,thirdLine,lastLine)
#define OLED_UPDATE_DISPLAY() \
    DISPLAY_WRITE();\
    OledDrawString(display);\
    OledUpdate()
// **** Declare any data types here ****

// **** Define any module-level, global, or external variables here ****
static char decodedChar = '\0';
static char display[200];
static char topLine[OLED_WIDTH];
static char secondLine[OLED_WIDTH];
static char thirdLine[OLED_WIDTH];
static char lastLine[OLED_WIDTH];
static int charCount = 0;
static int line1Count = 0;
static int clearFlag = 0;
static int resetFlag = 0;

// **** Declare any function prototypes here ****
static void OledTopClear(void);
static void OledTopAppend(char data);
static void OledBottomAppend(char data);
// **** Define any module-level, global, or external variables here ****

// **** Declare any function prototypes here ****

int main() {
    BOARD_Init();


    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_16, BOARD_GetPBClock() / 16 / 100);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T2);
    INTSetVectorPriority(INT_TIMER_2_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_2_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T2, INT_ENABLED);

    /************2******************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     *****************************************************************************/
    OledInit();

    //checks if MorseInit has an event
    if (MorseInit() == STANDARD_ERROR) {
        OledDrawString("ERROR\nMorseInit() Failed\n");
        OledUpdate();
        FATAL_ERROR();
    } else {
        sprintf(topLine, "%s", "MorseInit() Success");
        OLED_UPDATE_DISPLAY();
        while (1) {



            if (eventMorse != MORSE_EVENT_NONE) {


                switch (eventMorse) {
                    case MORSE_EVENT_DOT:
                        if (clearFlag == 0) {//Clear success message
                            clearFlag = 1; //Event only happens once
                            OledTopClear();
                        }
                        resetFlag = 0; ////Clear flag
                        decodedChar = MorseDecode(MORSE_CHAR_DOT);
                        OledTopAppend(MORSE_CHAR_DOT);
                        break;
                    case MORSE_EVENT_DASH:
                        if (clearFlag == 0) {//Clear success message
                            clearFlag = 1; //Event only happens once
                            OledTopClear();
                        }
                        resetFlag = 0; //Clear flag
                        decodedChar = MorseDecode(MORSE_CHAR_DASH);
                        OledTopAppend(MORSE_CHAR_DASH);
                        break;
                    case MORSE_EVENT_INTER_LETTER:
                        OledTopClear();
                        decodedChar = MorseDecode(MORSE_CHAR_END_OF_CHAR);
                        if (resetFlag != 1) { //Only Append if flag is not set
                            if (decodedChar != STANDARD_ERROR) {
                                OledBottomAppend(decodedChar); //Decoded letter
                            } else {//Appends # for STANDARD_ERROR
                                OledBottomAppend(MORSE_CHAR_END_OF_CHAR);
                            }
                        }
                        MorseDecode(MORSE_CHAR_DECODE_RESET);
                        break;
                    case MORSE_EVENT_INTER_WORD:
                        OledTopClear();
                        decodedChar = MorseDecode(MORSE_CHAR_END_OF_CHAR);
                        if (resetFlag != 1) { //Only Append if flag is not set
                            if (decodedChar != STANDARD_ERROR) {
                                OledBottomAppend(decodedChar); //Decoded letter
                            } else {//Appends # for STANDARD_ERROR
                                OledBottomAppend(MORSE_CHAR_END_OF_CHAR);
                            }
                            OledBottomAppend(SPACE); //Append a space
                        }
                        MorseDecode(MORSE_CHAR_DECODE_RESET);
                        break;
                    case MORSE_EVENT_NONE:
                        break;

                        //break;
                }

                eventMorse = MORSE_EVENT_NONE; //Reset morseEvents

            }
        }

        /******************************************************************************
         * Your code goes in between this comment and the preceding one with asterisks.
         *****************************************************************************/

        while (1);
    }
}

void __ISR(_TIMER_2_VECTOR, IPL4AUTO) TimerInterrupt100Hz(void) {
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    //******** Put your code here *************//
    eventMorse = MorseCheckEvents();
}

static void OledTopClear(void) {
    STRING_EMPTY(topLine);
    OLED_UPDATE_DISPLAY();
    line1Count = 0;
}

static void OledTopAppend(char data) {
    char x;
    if (line1Count <= OLED_WIDTH - 1)
        x = 'a';
    else if (line1Count > OLED_WIDTH - 1)
        x = 'b';

    switch (x) {
        case 'a':
            topLine[line1Count] = data;
            line1Count++;
            OLED_UPDATE_DISPLAY();
            break;

        case 'b':
            STRING_EMPTY(secondLine);
            STRING_EMPTY(thirdLine);
            STRING_EMPTY(lastLine);
            charCount = 0; //Reset count
            resetFlag = 1; //Set flag
            break;
    }

}

static void OledBottomAppend(char data) {

    char a;

    if (charCount <= OLED_WIDTH - 1)
        a = 'a';
    else if (charCount <= ((OLED_WIDTH) * 2) - 1)
        a = 'b';
    else if (charCount <= ((OLED_WIDTH)* 3) - 1)
        a = 'c';
    

    switch (a) {
        case 'a':
            secondLine[charCount] = data;
            charCount++;
            break;
        case 'b':
            thirdLine[(charCount)-(OLED_WIDTH)] = data;
            charCount++;
            break;
        case 'c':
            lastLine[(charCount) -((OLED_WIDTH) * 2)] = data;
            charCount++;
            break;
        default:
            strcpy(secondLine, thirdLine);
            strcpy(thirdLine, lastLine);
            STRING_EMPTY(lastLine); //Empty string
            charCount -= (OLED_WIDTH);
            OledBottomAppend(data); //Recursively call OledBottomAppend to print passed data
            break;
    }
    OLED_UPDATE_DISPLAY();



}
