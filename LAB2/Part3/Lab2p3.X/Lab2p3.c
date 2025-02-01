
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include <p18f4620.h>

#include "../../../Drivers/RGB_LED/RGB_LED.h"

#define delay 17000

#pragma config OSC = INTIO67
//#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF

// Prototype Area
void Delay_One_Sec();

void main(void) {

    struct RGB_LED led;
    RGB_LED_Init(&led, &PORTC, &TRISC, 0, 1, 2);

    while (1) {

        for(int i = 0; i < 8; i++){
            
            RGB_LED_Set_Color_Basic(&led, i);
            RGB_LED_Update(&led);
            
            Delay_One_Sec();
            
        }
    }
}

void Delay_One_Sec() {
    for (int I = 0; I < delay; I++);
}
