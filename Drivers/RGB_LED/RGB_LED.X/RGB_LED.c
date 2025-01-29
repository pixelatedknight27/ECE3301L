
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include <math.h>
#include <p18f4620.h>

#include "UART.h"
#include "RGB_LED.h"

#pragma config OSC = INTIO67
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF
#define delay 5

// Prototype Area to place all the references to the routines used in the program

void main(void) {
    TRISB = 0x00; // make PORTB as all outputs

    LATB = 0x00;

    //  Init_UART();

    //  declare LED
    struct RGB_LED led1;

    //  initialize LED Port and Pin
    //  Port B, Pins 
    //  R: PORTB0
    //  G: PORTB1
    //  B: PORTB2
    RGB_LED_Init(&led1, &LATB, 0, 1, 2);
    
    //  Set brightness of LED (0-255)
    // a makeshift PWM value
    RGB_LED_Set_Color(&led1, 255, 255, 255);

    while (1) {

        RGB_LED_Update(&led1);
        // RGB_LED_Print_Status(&led1);
    }
}