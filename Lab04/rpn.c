// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Stack.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries


// **** Set macros and preprocessor directives ****

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****
/*
 * Function prototype for ProcessBackspaces() - This function should be defined
 * below main after the related comment.
 */
int ProcessBackspaces(char *rpn_sentence);

// If this code is used for testing, rename main to something we can call from 
//our testing code. We
// also skip all processor configuration and initialization code.
#ifndef LAB4_TESTING

int main()
{
    BOARD_Init();
#else

int their_main(void)
{
#endif // LAB4_TESTING

    /******************************** Your custom code goes below here *******************************/
    //prints welcome message at start of program
    printf("Welcome to Kameron's RPN calculator.\r\n");
    //constant variables
    char input[60];
    char *inTest;
    float operand, operand2;
    float in1, in2;
    float out;
    int testStack1, testStack2;
    int test1, test2;

    struct Stack stack;
    //starts the stack
    StackInit(&stack);

    /*************************************************************************************************/

    // You can never return from main() in an embedded system (one that lacks an operating system).
    // This will result in the processor restarting, which is almost certainly not what you want!
    while (1) {


        //prints instructions at start of each cycle
        printf("Enter floats and operators in RPN form! (+, -, *, /): \n");

        //gets input from keyboard

        fgets(input, 60, stdin);

        //tokenizes the input from keyboard into seperate chars to use

        inTest = strtok(input, " ");

        while (inTest != NULL) {
            //converts string into float
            operand = atof(inTest);


            //checks to see if x is an operator
            if (operand != 0 || *inTest == '0') {
                //push operand to stack
                test1 = StackPush(&stack, operand);
            }//checks if an operand is being used
            else if ((*inTest == '+') || (*inTest == '-') || (*inTest == '*')
                    || (*inTest == '/')) {
                //pops the stack and also gives0/1 to testStack
                //to see if it worked
                testStack1 = StackPop(&stack, &in1);
                testStack2 = StackPop(&stack, &in2);

                //checks to see if there was an error in the stack
                //checks the operators and deals the apprioate actions
                if (*inTest == '+') {
                    //get values of in1 + in2
                    out = in1 + in2;
                    //pushes value into the stack
                    //test2 checks if there is an error in
                    //stack
                    test2 = StackPush(&stack, out);
                    if (testStack1 == STANDARD_ERROR) {
                        printf("ERROR: Not Enough operands before operator\n");
                        break;
                    } else if (test2 == STANDARD_ERROR) {
                        printf("ERROR: No more room on Stack");
                        break;
                    }

                } else if (*inTest == '-') {
                    //get values of in1 + in2
                    out = in1 - in2;
                    //pushes value into the stack
                    //test2 checks if there is an error in
                    //stack
                    test2 = StackPush(&stack, out);
                    if (testStack1 == STANDARD_ERROR ||
                            testStack2 == STANDARD_ERROR) {
                        printf("ERROR: Not Enough operands before operator\n");
                        break;
                    } else if (test2 == STANDARD_ERROR) {
                        printf("ERROR: No more room on Stack");
                        break;
                    }
                } else if (*inTest == '*') {
                    //get values of in1 + in2
                    out = in1*in2;
                    //pushes value into the stack
                    //test2 checks if there is an error in
                    //stack
                    test2 = StackPush(&stack, out);
                    if (testStack1 == STANDARD_ERROR ||
                            testStack2 == STANDARD_ERROR) {
                        printf("ERROR: Not Enough operands before operator\n");
                        break;
                    } else if (test2 == STANDARD_ERROR) {
                        printf("ERROR: No more room on Stack");
                        break;
                    }
                } else if (*inTest == '/') {
                    //get values of in1 + in2
                    out = in1 / in2;
                    //pushes value into the stack
                    //test2 checks if there is an error in
                    //stack
                    test2 = StackPush(&stack, out);
                    if (testStack1 == STANDARD_ERROR ||
                            testStack2 == STANDARD_ERROR) {
                        printf("ERROR: Not Enough operands before operator\n");
                        break;
                    } else if (test2 == STANDARD_ERROR) {
                        printf("ERROR: No more room on Stack");
                        break;
                    }
                }

            } else if (*inTest != '9' || *inTest != '0' || *inTest != '8' ||
                    *inTest != '7' || *inTest != '6' || *inTest != '5' || *inTest != '4' ||
                    *inTest != '3' || *inTest != '2' || *inTest != '1' ||
                    *inTest != '-' || *inTest != '*' || *inTest != '/' ||
                    *inTest != '/') {
                printf("ERROR: Invalid Character in the RPN String \n");
                break;
            }


            inTest = strtok(NULL, " ");
        }
        if (StackGetSize(&stack) > 1) {
            printf("ERROR: Invalid RPN calculation: more or less than one item in the stack");
        }
        if (StackGetSize(&stack) == 1) {
            StackPop(&stack, &out);
            printf("Answer: %f\n", (double) out);
        }

    }
    while (1);
}

/**
 * Extra Credit: Define ProcessBackspaces() here - This function should read through an array of
 * characters and when a backspace character is read it should replace the preceding character with
 * the following character. It should be able to handle multiple repeated backspaces and also
 * strings with more backspaces than characters. It should be able to handle strings that are at
 * least 256 characters in length.
 * @param rpn_sentence The string that will be processed for backspaces. This string is modified in
 *                     place.
 * @return Returns the size of the resultant string in `rpn_sentence`.
 */
int ProcessBackspaces(char *rpn_sentence)
{
    return 0;
}



