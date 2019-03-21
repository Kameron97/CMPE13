//Kameron Gill
//kgill2@ucsc.edu
//lab4

#include "BOARD.h"
#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 20


//initializes stack at -1, and also sets initalization status to  1

void StackInit(struct Stack *stack)
{
    stack->currentItemIndex = -1;
    stack->initialized = 1; //1 = true;
}

//adds a number to stack
//checks if it is true

int StackPush(struct Stack *stack, float value)
{
    //checks to see if stack is initialized and if stack is full
    if (stack->initialized == 0 || stack->currentItemIndex == STACK_SIZE - 1) {
        //if so, returns a failure
        return STANDARD_ERROR;

    } else {
        stack -> currentItemIndex++;
        stack -> stackItems[stack -> currentItemIndex] = value;
        return SUCCESS;
    }
}
//return top of stack into value point location

int StackPop(struct Stack *stack, float *value)
{
    //checks to see if stack is initialized and if stack is full
    if (stack->initialized == 0 || stack->currentItemIndex == STACK_SIZE - 1) {
        //if so, returns a failure
        return STANDARD_ERROR;
    } else {
        *value = stack->stackItems[stack->currentItemIndex];
        stack->currentItemIndex--;
        return SUCCESS;
    }
}

//checks to see if stackisempty

int StackIsEmpty(const struct Stack *stack)
{
    if (stack->currentItemIndex == -1) {
        return 1;
    } else {
        return 0;
    }
}

//checks to see if stack is full

int StackIsFull(const struct Stack *stack)
{
    if (stack->currentItemIndex == STACK_SIZE - 1) {
        return 1;
    } else {
        return 0;
    }
}

//returns size of the stacke

int StackGetSize(const struct Stack *stack)
{
    if (stack->initialized == 0) {
        return SIZE_ERROR;
    } else {
        return stack->currentItemIndex + 1;

    }
}