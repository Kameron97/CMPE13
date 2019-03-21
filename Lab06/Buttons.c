#include <stdint.h>

#include "Buttons.h"
#include "Leds.h"

static uint8_t prevState = 0x00;
static uint8_t sample[BUTTONS_DEBOUNCE_PERIOD];

//initialize buttons

void ButtonsInit(void)
{
    TRISD |= 0x00E0;
    TRISF |= 0x0002;
}

uint8_t ButtonsCheckEvents(void)
{
    uint8_t buttonEvents = BUTTON_EVENT_NONE; //Initialized to none

    int i = BUTTONS_DEBOUNCE_PERIOD; //Initialize loop variable

    char x = 'x';

    //Stores in array past samples based on the size of
    //the BUTTONS_DEBOUNCE_PERIOD macro
    while (i) {
        if (i == 1) {
            sample[0] = BUTTON_STATES();
            i = BUTTONS_DEBOUNCE_PERIOD - 1; //Loop variable -1 of elements
            break;
        }
        sample[i - 1] = sample[i - 2];
        i--;
    }

    //Generates boolean to check if past samples are equal
    int sampleBool = 1; //TRUE
    while (i) { //Iterates 1 less time since other samples must be equal to oldest sample
        if (sample[i - 1] != sample[BUTTONS_DEBOUNCE_PERIOD - 1]) {
            sampleBool = 0; //Set to FALSE if not equal 
            break;
        }
        i--;
    }
    if ((prevState & 0x01) < ((sample[BUTTONS_DEBOUNCE_PERIOD - 1])& 0x01))
        x = 'a';
    if ((prevState & 0x01) > ((sample[BUTTONS_DEBOUNCE_PERIOD - 1])& 0x01))
        x = 'b';
    if ((prevState & 0x02) < ((sample[BUTTONS_DEBOUNCE_PERIOD - 1])& 0x02))
        x = 'c';
    if ((prevState & 0x02) > ((sample[BUTTONS_DEBOUNCE_PERIOD - 1])& 0x02))
        x = 'd';
    if ((prevState & 0x04) < ((sample[BUTTONS_DEBOUNCE_PERIOD - 1])& 0x04))
        x = 'e';
    if ((prevState & 0x04) > ((sample[BUTTONS_DEBOUNCE_PERIOD - 1])& 0x04))
        x = 'f';
    if ((prevState & 0x08) < ((sample[BUTTONS_DEBOUNCE_PERIOD - 1])& 0x08))
        x = 'g';
    if ((prevState & 0x08) > ((sample[BUTTONS_DEBOUNCE_PERIOD - 1])& 0x08))
        x = 'h';
    if (sampleBool) {

        if (prevState != sample[BUTTONS_DEBOUNCE_PERIOD - 1]) {


            switch (x) {
            case 'a':
                buttonEvents |= BUTTON_EVENT_1DOWN;
                break;

            case 'b':
                buttonEvents |= BUTTON_EVENT_1UP;
                break;
            case 'c':
                buttonEvents |= BUTTON_EVENT_2DOWN;
                break;
            case 'd':
                buttonEvents |= BUTTON_EVENT_2UP;
                break;
            case 'e':
                buttonEvents |= BUTTON_EVENT_3DOWN;
                break;
            case 'f':
                buttonEvents |= BUTTON_EVENT_3UP;
                break;
            case 'g':
                buttonEvents |= BUTTON_EVENT_4DOWN;
                break;

            case 'h':
                buttonEvents |= BUTTON_EVENT_4UP;
                break;

            }
            prevState = sample[BUTTONS_DEBOUNCE_PERIOD - 1]; //Previous state equal to last sample

        }
    }

    return buttonEvents;



}

