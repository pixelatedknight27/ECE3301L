
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include <p18f4620.h>
#include <stdint.h>

#pragma config OSC = INTIO67
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF

#include "../../../Drivers/RGB_LED/RGB_LED.h"

void main(void)
{
    
uint8_t in_sw;
    
    TRISA = 0b00001111;
    ADCON1 = 0x0F;
    
    struct RGB_LED led;
    RGB_LED_Init(&led, &PORTC, &TRISC, 0, 1, 2);
    
    
    while (1) {
        in_sw = PORTA;
        in_sw = in_sw & 0x0F;
        
        RGB_LED_Set_Color_Basic(&led, in_sw & 0b00000111);
        RGB_LED_Update(&led);
    }
} 
