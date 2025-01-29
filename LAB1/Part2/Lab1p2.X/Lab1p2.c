#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include <p18f4620.h>
#include "UART.h"

#pragma config OSC = INTIO67
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF

void main(void) {
    char k;
    float t;
    Init_UART();
    while (1) {
        t = 19.909;
        printf("\r\n\nHello World! Floating Point Print with 1 decimal place t= %6.1f", t);
        printf("\r\nHello World! Floating Point print with 2 decimal places t= %6.2f", t);
    }
}