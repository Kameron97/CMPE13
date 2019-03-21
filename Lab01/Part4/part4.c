/*
 * File:   Part4.c
 * Author: Kameron Gill
 * Student ID: 1476833
 * email: kgill2@ucsc.edu
 * Lab 1
 *
 * Created on January 9, 2018, 4:26 PM
 */


#include "xc.h"
#include "BOARD.h"

void main(void)
{
    OledInit();
    OledDrawString("Hello World!\n");
    OledUpdate();
    while (1);

}
