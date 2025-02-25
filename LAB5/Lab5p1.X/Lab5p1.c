/*
 * File:   Lab5p1.c
 * Author: maxgr
 *
 * Created on February 25, 2025, 4:58 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include <math.h>
#include <p18f4620.h>

#include "../../Drivers/ADC.h"
#include "../../Drivers/UART.h"
#include "../../Drivers/RGB_LED/RGB_LED.h"
#include "../../Drivers/seven_segment/seven_segment.h"

  #pragma config OSC = INTIO67

//  High speed clock rate for GPIO PWM bit bang.
//  Use COM terminal speed of 19200.
//#pragma config OSC = HS     
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF

//  Prototype Area to place all the references to the routines used in the program
struct seven_seg seven_seg0;


void main(void) {

    Init_UART();
    Init_ADC();
    
    //  declare LED
    struct RGB_LED led0, led1, led2;

    RGB_LED_Init(&led0, &PORTC, &TRISC, 0, 1, 2);
    RGB_LED_Init(&led1, &PORTC, &TRISC, 3, 4, 5);
    RGB_LED_Init(&led2, &PORTE, &TRISE, 0, 1, 2);
    
    //  Set brightness of LED using basic predefined colors
    RGB_LED_Set_Color_Basic(&led0, WHITE);
    RGB_LED_Set_Color_Basic(&led1, WHITE);
    RGB_LED_Set_Color_Basic(&led2, WHITE);
    
    seven_seg_init(&seven_seg0, &PORTB, &TRISB);
    
    RGB_LED_Update(&led0);
    RGB_LED_Update(&led1);
    RGB_LED_Update(&led2);
    
    while (1) {
        
        //  cast adc reading to a value between 0 and 255
        uint8_t adc_reading_0 = 255 * (1 - Read_Ch_Volt(0)/1024);
        uint8_t adc_reading_1 = 255 * (1 - Read_Ch_Volt(1)/1024);
            
        printf("ADC_0: %d\r\nADC_1: %d\r\n\r\n", adc_reading_0, adc_reading_1);
            
        for(int i = 0; i <= 7; i++){
            seven_seg_set_num(&seven_seg0, i);
            RGB_LED_Set_Color_Basic(&led0, i);
            RGB_LED_Update(&led0);
            
            for(int j = 32767; j > 0; j--);
            
        }
        
        RGB_LED_Update(&led0);
        RGB_LED_Update(&led1);
        RGB_LED_Update(&led2);
        
    }
}
