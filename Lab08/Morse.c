//Kameron Gill
//kgill2@ucsc.edu

//Lab 8
//Morse.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "Tree.h"
#include "Buttons.h"
#include "Morse.h"
#include "BOARD.h"



//static variables
static Node *tree = NULL;
static Node *temp = NULL;
static uint8_t buttons = 0;
static int count = 0;


//letters for morse decoding
static char morseLetters[] = {'\0', 'E',
    'I', 'S', 'H', '5', '4', 'V', '\0', '3', 'U', 'F', '\0', '\0', '\0', '\0', '2',
    'A', 'R', 'L', '\0', '\0', '\0', '\0', '\0', 'W', 'P', '\0', '\0', 'J', '\0', '1',
    'T', 'N', 'D', 'B', '6', '\0', 'X', '\0', '\0', 'K', 'C', '\0', '\0', 'Y', '\0', '\0',
    'M', 'G', 'Z', '7', '\0', 'Q', '\0', '\0', 'O', '\0', '8', '\0', '\0', '9', '0',};

static enum {
    WAITING,
    DOT,
    DASH,
    INTER_LETTER
} state = WAITING;



//functions

//MorseInit()
//checks to see if adt can be made and returns error/success depending if
//tree was succesful
//also initializes buton

int MorseInit(void) {
    ButtonsInit();
    temp = TreeCreate(6, morseLetters);

    if (temp == NULL)
        return STANDARD_ERROR;
    else {
        state = WAITING;
        tree = temp;
        return SUCCESS;

    }
}

char MorseDecode(MorseChar in) {
    char x;

    if (in == MORSE_CHAR_DOT)
        x = 'a';
    else if (in == MORSE_CHAR_DASH)
        x = 'b';
    else if (in == MORSE_CHAR_END_OF_CHAR)
        x = 'c';
    else if (in == MORSE_CHAR_DECODE_RESET)
        x = 'd';


    switch (x) {
        case 'a':
            tree = tree->leftChild;
            return SUCCESS;
            break;
        case 'b':
            tree = tree-> rightChild;
            return SUCCESS;
            break;
        case 'c':
            return tree->data;
            break;
        case 'd':
            tree = temp;
            return SUCCESS;
            break;

        default:
            tree = temp;
            return STANDARD_ERROR;
            break;
    }
}

MorseEvent MorseCheckEvents(void) {
    count++;
    buttons = ButtonsCheckEvents();

    if (state == WAITING) {
        count = 0;
        if (buttons == BUTTON_EVENT_4DOWN) {
            state = DOT;
        } else {
            state = WAITING;
        }
    } else if (state == DOT) {
        if (buttons == BUTTON_EVENT_4UP) {
            count = 0;
            state = INTER_LETTER;
            return MORSE_EVENT_DOT;
        }
        if (count > MORSE_EVENT_LENGTH_DOWN_DASH) {
            state = DASH;
        }
    } else if (state == DASH) {
        if (buttons == BUTTON_EVENT_4UP) {
            count = 0;
            state = INTER_LETTER;
            return MORSE_EVENT_DASH;
        }
    } else if (state == INTER_LETTER) {
        if (count >= MORSE_EVENT_LENGTH_UP_INTER_LETTER) {
            state = WAITING;
            return MORSE_EVENT_INTER_WORD;
        }
        if (buttons == BUTTON_EVENT_4DOWN) {
            if (count >= MORSE_EVENT_LENGTH_UP_INTER_LETTER) {
                count = 0;
                state = DOT;
                return MORSE_EVENT_INTER_LETTER;
            }
            count = 0;
            state = DOT;
        }
    } else {
        FATAL_ERROR();
    }
    return MORSE_EVENT_NONE;
}
