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
#include "CMath.h"


// **** Set macros and preprocessor directives ****

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****

#define QX 1.5
#define QY 2.8
#define PX -2.3
#define PY 8.6
#define DX (QX-PX)
#define DY (QY-PY)

int main()
{
    BOARD_Init();
    {

        /******************************** Your custom code goes below here *******************************/
        //testing for hypot
        double mathHypot = hypotf(DX, DY);
        double testEnorm1 = enorm(-2.3, 8.6, 1.5, 2.8);
        double test1 = hypotf(3, 4);
        double test2 = hypotf(6, 8);

        printf("Hypot returned %f and should return %f\r\n", mathHypot, 6.9340);
        printf("Enorm returned %f and should return %f\r\n", testEnorm1, 6.9340);


        // printf("Hypot returned %f and should return %f\r\n", test1, 5.00);
        //printf("Hypot returned %f and should return %f\r\n", test2, 10.00);

        printf("\n");

        //testing for arc tan
        double mathAtan2 = atan2(QX, QY);
        double arcTangent1 = arctangent2(QX, QY);
        double arcTanget2 = arctangent2(30, 60);
        double testAtan2 = atan2(30, 60);


        printf("Atan2 returned %f and should return %f\r\n", mathAtan2, .4918);
        printf("Arctangent2 returned %f and should return %f\r\n", arcTangent1, .4918);
        printf("Atan2 returned %f and should return %f\r\n", testAtan2, .463);
        printf("Arctangent2 returned %f and should return %f\r\n", arcTanget2, .463);





        /*************************************************************************************************/

        // You can never return from main() in an embedded system (one that lacks an operating system).
        // This will result in the processor restarting, which is almost certainly not what you want!
        while (1);
    }
}


