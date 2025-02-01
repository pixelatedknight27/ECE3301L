
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

    struct RGB_LED led0;
    RGB_LED_Init(&led0, &LATC, &TRISC, 0, 1, 2);

    struct RGB_LED led1;
    RGB_LED_Init(&led1, &LATD, &TRISD, 2, 4, 5); // solder bad on port 3 :(

    RGB_LED_Colors led0_colors[8] = {PURPLE, YELLOW, BLUE, CYAN, RED, GREEN, WHITE, OFF};
    RGB_LED_Colors led1_colors[8] = {CYAN, YELLOW, WHITE, OFF, GREEN, PURPLE, BLUE, RED};

    while (1) {

        for(int i = 0; i < 8; i++){
            
            RGB_LED_Set_Color_Basic(&led0, led0_colors[i]);
            RGB_LED_Set_Color_Basic(&led1, led1_colors[i]);
            
            RGB_LED_Update(&led0);
            RGB_LED_Update(&led1);
            
            Delay_One_Sec();
            
        }
    }
}

void Delay_One_Sec() {
    for (int I = 0; I < delay; I++);
}
