
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include <math.h>
#include <p18f4620.h>

#include "../../../Drivers/UART.h"
#include "../../../Drivers/RGB_LED/RGB_LED.h"

//  #pragma config OSC = INTIO67

//  High speed clock rate for GPIO PWM bit bang.
//  Use COM terminal speed of 19200.
#pragma config OSC = HS     
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF

//  Prototype Area to place all the references to the routines used in the program

void main(void) {

    Init_UART();
    
    //  constants
    uint8_t rgb_timer = 0;      //  initialize cycle timer
    uint8_t rgb_speed = 128;    //  set cycle speed

    //  rgb value initialization 
    uint8_t red = 255;
    uint8_t green = 0;
    uint8_t blue = 0;
    int phase = 0;

    //  declare LED
    struct RGB_LED led;

    //  initialize LED Port and Pin
    //  set Port B to all outputs
    //  set Port B to 0x00
    
    //  Port B, Pins:
    //  R: PORTB0
    //  G: PORTB1
    //  B: PORTB2
    RGB_LED_Init(&led, &PORTC, &TRISC, 0, 1, 2);
    
    //  Set brightness of LED (0-255)
    RGB_LED_Set_Color(&led, red, green, blue);
    
    TRISA = 0b00001111;
    ADCON1 = 0x0F;

    while (1) {
        
        //  cycle through intensities
        
        if(rgb_timer == rgb_speed){
            uint8_t in_sw = PORTA;
            
            if(phase == 0){
                red--;
                green++;
                if(green == 255){
                    phase = 1;
                }
            }
            else if(phase == 1){
                green--;
                blue++;
                if(blue == 255){
                    phase = 2;
                }
            }
            else if(phase == 2){
                blue--;
                red++;
                if(red == 255){
                    phase = 0;
                }
            }
            
            //  scale rgb by adc reading
            RGB_LED_Set_Color(&led, red/(16-in_sw), green/(16-in_sw), blue/(16-in_sw));
            
//            RGB_LED_Print_Status(&led); //  LED debug print - baud 19200
            
//            printf("%d\r\n", in_sw);
            
            rgb_timer = 0;
        }
        
        rgb_timer++;
        
        RGB_LED_Update(&led);
        
    }
}