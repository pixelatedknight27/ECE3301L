
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
    
    TRISB = 0b00000000;        //  set all pins of PORTB to output
    TRISA = 0b00001111;        //  set bottom 4 pins of PORTA to input
    ADCON1 = 0x0F;             //  disable analog ADC
    
    
    while (1)
    {
        in_sw = PORTA;         //  read PORTA
        in_sw = in_sw & 0x0F;  //  mask out upper 4 bits
        PORTB = in_sw;         //  write result to PORTB
    }
} 