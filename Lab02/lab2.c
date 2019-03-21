// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <math.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>


// User libraries


// **** Set macros and preprocessor directives ****

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****
double Round(double operand);
double AbsoluteValue(double x);
double FahrenheitToCelsius(double x);
double CelsiusToFahrenheit(double x);
double Tangent(double x);
double Average(double x, double y);
double Round(double x);



// If this code is used for testing, rename main to something we can call from our testing code.
#ifndef LAB2_TESTING

int main(void) {
    BOARD_Init();
#else

int their_main(void) {

#endif // LAB2_TESTING

    /******************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     *****************************************************************************/
    char operator; //inputs for scanf
    double oper1, oper2; //operand variables
    char c;

    //print welcome message 
    printf("Welcome to Kameron's calculator!\n");

    while (1) {
        printf("Enter a mathematical operation to perform (*,/,+,-,v,a,c,f,t,r): ");
        scanf(" %c", &operator);
        printf("\n");

        //checking for + operator
        if (operator == '+') {
            printf("%s", "Please enter first operand:  ");
            scanf("%f", &oper1);
            printf("\n");


            printf("%s", "Please enter second operand:  ");
            scanf("%f", &oper2);
            printf("\n");

            //print out of statement
            printf("%s%f%c%f%s", "Result of ( ", oper1, '+', oper2, " ): ");
            printf("%f", oper1 + oper2);
            printf("\n");
        }

        //multiply function 
        if (operator == '*') {
            printf("%s", "Please enter first operand:  ");
            scanf(" %f", &oper1);
            //printf("%f", oper1);
            printf("\n");


            printf("%s", "Please enter second operand:  ");
            scanf(" %f", &oper2);
            // printf("%f", oper2);
            printf("\n");

            //print out of statement
            printf("%s%f%c%f%s", "Result of ( ", oper1, '*', oper2, " ): ");
            printf("%f", oper1 * oper2);
            printf("\n");
        }

        //function for - check
        if (operator == '-') {
            printf("%s", "Please enter first operand:  ");
            scanf(" %f", &oper1);
            //printf("%f", oper1);
            printf("\n");


            printf("%s", "Please enter second operand:  ");
            scanf(" %f", &oper2);
            //printf("%f", oper2);
            printf("\n");

            //print out of statement
            printf("%s%f%c%f%s", "Result of ( ", oper1, '-', oper2, " ): ");
            printf("%f", oper1 - oper2);
            printf("\n");
        }

        //function to check for /
        if (operator == '/') {
            printf("%s", "Please enter first operand:  ");
            scanf(" %f", &oper1);
            //printf("%f", oper1);
            printf("\n");


            printf("%s", "Please enter second operand:  ");
            scanf(" %f", &oper2);
            // printf("%f", oper2);
            printf("\n");


            //print out of statement
            if (oper2 != 0) {
                printf("%s%f%c%f%s", "Result of ( ", oper1, '/', oper2, " ): ");
                printf("%f", oper1 / oper2);
                printf("\n");
            }//if operand2 is 0 prints out automatic 0
            else {
                printf("%s%f%c%f%s", "Result of ( ", oper1, '/', oper2, " ): ");
                printf("%s", "0");
                printf("\n");
            }
        }


        //average operator
        if (operator == 'v') {
            printf("%s", "Please enter first operand:  ");
            scanf(" %f", &oper1);
            printf("%f", oper1);
            printf("\n");


            printf("%s", "Please enter second operand:  ");
            scanf(" %f", &oper2);
            printf("%f", oper2);
            printf("\n");

            //print out of statement
            printf("%s%f%s%f%s", "Average of ( ", oper1, " and ", oper2, " ): ");
            printf("%f", Average(oper1, oper2));
            printf("\n");
        }

        //absolute value
        if (operator == 'a') {
            printf("%s", "Please enter first operand:  ");
            scanf(" %f", &oper1);
            //printf("%f", oper1);
            printf("\n");

            //print absolute value
            printf("%s%f%s%f", "Result of  | ", oper1, " |: ", AbsoluteValue(oper1));
        }
        //celsius -> fahrenheit
        if (operator == 'c') {
            printf("%s", "Please enter first operand:  ");
            scanf(" %f", &oper1);
            //printf("%f", oper1);
            printf("\n");

            //print conversion message
            printf("%s%f%s%f", "Result of ", oper1, " deg->F: ", CelsiusToFahrenheit(oper1));
            printf("\n");
        }

        //fahreneit -> celius
        if (operator == 'f') {
            printf("%s", "Please enter first operand:  ");
            scanf(" %f", &oper1);
            //printf("%f", oper1);
            printf("\n");

            //print conversion message
            printf("%s%f%s%f", "Result of ", oper1, " deg->C: ", FahrenheitToCelsius(oper1));
            printf("\n");
        }


        //tangent conversion
        if (operator == 't') {
            printf("%s", "Please enter first operand:  ");
            scanf(" %f", &oper1);
            //printf("%f", oper1);
            printf("\n");

            //print conversion message
            printf("%s%f%s%f", "Result of ", oper1, " tan ", Tangent(oper1));
            printf("\n");
        }





        //get another operator 





    }




    /******************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     *****************************************************************************/
    while (1);
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double x) {
    if (x < 0) {
        x = x * -1;
    }
    return x;

}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/

double CelsiusToFahrenheit(double x) {
    x = (9.0 / 5.0) * x + 32.0;
    return x;
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/

double FahrenheitToCelsius(double x) {
    x = (x - 32.0) / (9 / 5);
    return x;
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/

double Average(double x, double y) {
    double result = (x + y) / 2.0;
    return result;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees (Note: Your tangent 
 * function relies on a call from the tangent function of math.h which uses 
 * radians).
 ********************************************************************************/

double Tangent(double x) {
    return tan(x * (3.14152926 / 180));

}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand) {
    return operand;
}

