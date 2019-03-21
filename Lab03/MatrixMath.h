/*
 * @File:   Lab3.c
 * @Author: Allen Aboytes (1478650)
 * @Section CMPE13L-01 (62374)
 * @Description: RPN Calculator
 */
// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
#include "Stack.h"

// **** Set macros and preprocessor directives ****
#define STRING_SIZE 60
// **** Define global, module-level, or external variables here ****
//#define LAB4_TESTING

// **** Declare function prototypes ****
/*
 * Function prototype for ProcessBackspaces() - This function should be defined
 * below main after the related comment.
 */
int ProcessBackspaces(char *rpn_sentence);
int IsOperation(char *operation);

// If this code is used for testing, rename main to something we can call from our testing code. We
// also skip all processor configuration and initialization code.
#ifndef LAB4_TESTING

int main()
{
    BOARD_Init();
#else

int main()
{
    BOARD_Init();

  
    char * testString1 = malloc(sizeof (char[STRING_SIZE]));
    testString1 = "1 2\b3 +"; // Should simplify to "1 3 +" 
    int size = ProcessBackspaces(testString1); // testString1 should now have "1 3 +" in it.
    printf("\n%d\n", size);
    //puts(testString1); // Print the string. This will not show \b chars!
#endif   // LAB4_TESTING

    /******************************** Your custom code goes below here ****************************/
        //Allocate memory for pointers
        char * rpnStr = malloc(sizeof (char[STRING_SIZE]));
        struct Stack *stack = (struct Stack*) malloc(sizeof (struct Stack));
        char *token = malloc(sizeof (rpnStr));
        float *op1 = malloc(sizeof (float));
        float *op2 = malloc(sizeof (float));
        float *result = malloc(sizeof (float));
        float val;
    
        printf("\nWelcome to Allen's RPN Calculator\n");
        while (1) {
    
            StackInit(stack); //Initialize Stack
    
            printf("\nEnter a RPN String (+ - / *)\n");
            printf("Separate operands and operations: ");
            fgets(rpnStr, STRING_SIZE, stdin); //Gets input string
            if (strlen(rpnStr) > 5) {
                token = strtok(rpnStr, " "); //Tokenizes on whitespace
                while (token != NULL) {
                    if (*token == '\n') {//if \n is found calculation loop terminated
                        break;
                    } else {
    
                        if (atof(token) != 0) {//if token is not operator
    
                            val = atof(token); //converts input value to float
    
                            if (StackPush(stack, val) == STANDARD_ERROR) {//Pushes value onto Stack
                                printf("ERROR: Stack Overflow, cannot Push!\n");
                                break;
                            }
                        } else if (IsOperation(token) == 1) {
                            //if token is operator Pop 2 values on Stack
                            if (StackPop(stack, op2) == SUCCESS && StackPop(stack, op1) == SUCCESS) {
                                switch (*token) {
                                case '+':
                                    StackPush(stack, (*op1 + *op2));
                                    break;
                                case '-':
                                    StackPush(stack, (*op1 - *op2));
                                    break;
                                case '/':
                                    if (*op2 != 0) {
                                        StackPush(stack, ((*op1) / (*op2)));
                                    } else {
                                        printf("ERROR: Cannot divide by 0\n");
                                        //Sets stack to full and produces error
                                        stack->currentItemIndex = STACK_SIZE;
                                    }
                                    break;
                                case '*':
                                    StackPush(stack, ((*op1) * (*op2)));
                                    break;
                                default:
                                    printf("ERROR: Invalid input RPN string!\n");
                                    break;
                                }
                            } else {
                                printf("ERROR: Not enough operands before operator\n");
                                break;
                            }
                        } else {
                            printf("ERROR: Invalid input RPN string!\n");
                            break;
                        }
                    }
                    token = strtok(NULL, " "); //Gets next token
                    if (token == NULL) {
                        if (StackGetSize(stack) == 1) {
                            StackPop(stack, result); //Pops result
                            printf("\nResult = %f\n", (double) *result);
                            break;
                        } else {
                            printf("ERROR: Invalid input RPN string!\n");
                            break;
                        }
                    }
                }
            } else {
                printf("ERROR: Invalid input RPN string!\n");
            }
        }
    /**********************************************************************************************/
    // You can never return from main() in an embedded system (one that lacks an operating system).
    // This will result in the processor restarting, which is almost certainly not what you want!
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
    int entered, out = 0;
    //loop iterates throught entered string as long as it can index
    for (entered = 0; entered < strlen(rpn_sentence) && rpn_sentence[entered]; entered++) {
        if (rpn_sentence[entered] != '\b') {
            rpn_sentence[out] = rpn_sentence[entered];
            out++; 
        }
    }
    return out;
}

/*
 * IsOperation() compares the input value to the an array of acceptable Operations
 * returns TRUE if it is acceptable
 */
int IsOperation(char *operation)
{
    char operators[4] = {'+', '-', '/', '*'};
    int opIndex, valid = 0;

    for (opIndex = 0; opIndex < 4; opIndex++) {

        if (*operation == operators[opIndex]) {

            valid = 1;
        }
    }

    return valid;

}
