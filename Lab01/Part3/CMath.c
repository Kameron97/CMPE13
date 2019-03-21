#include "CMath.h"


float myabs(float x);

float myabs(float x)
{
    //checks to see if x is negative
    if (x < 0) {
        x = x* -1;
    }

    return x;
}
//alogrithm for arctangent conversions
float arctangent2(float y, float x)
{
    float absoluteY;
    float r, theta;

    //get absolute value of each varaible
    absoluteY = myabs(y);

    //algorithm for arctangent

    if (x > 0) {
        r = (x - absoluteY) / (x + absoluteY);
        theta = 0.1963 * (r * r * r) - .9817 * r + (3.1415 / 4.0);

    } else {
        r = (x + absoluteY) / (x - absoluteY);
        theta = 0.1963 * (r * r * r) - .9817 * r + (3.0 * 3.1415 / 4.0);
    }

    if (y < 0)
        theta = theta * -1.0;

    return theta;

}


//algorithm for the hypotenuseconversion
float enorm(float px, float py, float qx, float qy)
{
    float absoluteX, absoluteY;
    float e, g, t, r, s;
    int i;

    absoluteX = myabs(qx - px);
    absoluteY = myabs(qy - py);

    if (absoluteX > absoluteY) {
        g = absoluteX;
        e = absoluteY;
    } else {
        g = absoluteY;
        e = absoluteX;
    }

    for (i = 0; i < 2; i++) {
        t = e / g;
        r = t * t;
        s = r / (4.0 + r);
        g = g + 2 * s * g;
        e = e * s;

        //i = i + 1.0;
    }
    return g;
}
