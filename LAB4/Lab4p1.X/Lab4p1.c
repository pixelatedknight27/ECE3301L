#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include <p18f4620.h>

#pragma config OSC = INTIO67
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF


void main() {
    char InA;
    char Result;
    ADCON1 = 0x0f;
    TRISA = 0x0F; // make sure PORT A is input
    TRISB = 0x0F; // make sure PORT B is input
    TRISC = 0x00; // make sure PORT C is output
    TRISD = 0x00; // make sure PORT D is output
    TRISE = 0x07; // make sure PORT E is input
    
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    
    while (1) {
        InA = PORTA; // Read from PORT A
        InA = InA & 0x0F; // Mask out upper 4 bits
        Result = (InA ^ 0x0F) + 1 ; // Take the 1?s complement for the lower 4 bits
//        Result = Result + 1;
        Result = Result & 0x0F; // Mask out the upper 4 bits
        PORTC = Result;
    }
}