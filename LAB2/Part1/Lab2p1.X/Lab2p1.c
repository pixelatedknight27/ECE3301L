
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include <p18f4620.h>

#pragma config OSC = INTIO67
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF

void main(void)
{
    
char in_sw;
    
    TRISB = 0b00000000;
    TRISA = 0b00001111;
    ADCON1 = 0x0F;
    
    
    while (1)
    {
        in_sw = PORTA;
        in_sw = in_sw & 0x0F;
        PORTB = in_sw;
    }
} 