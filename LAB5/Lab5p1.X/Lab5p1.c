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
struct seven_seg seven_seg1;


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
    seven_seg_init(&seven_seg1, &PORTD, &TRISD);
    
    RGB_LED_Update(&led0);
    RGB_LED_Update(&led1);
    RGB_LED_Update(&led2);
    
    while (1) {
        
        //  cast adc reading to a value between 0 and 255
        float adc_reading_0 = 5 * Read_Ch_Volt(0)/1024;
        float adc_reading_1 = 5 * Read_Ch_Volt(1)/1024;
       
        float tmp_sens_reading = (adc_reading_0 - 1.035) / (-0.0055); 
        float light_sens_reading = adc_reading_1;
        
        tmp_sens_reading = tmp_sens_reading * 1.8 + 32;
        
        uint8_t tmp_sens_trunc = (uint8_t)tmp_sens_reading;
            
        printf("voltage: %f\r\ntemp: %f\r\ntemp trunc: %d\r\nlight voltage: %f\r\n\r\n", adc_reading_0, tmp_sens_reading, tmp_sens_trunc, light_sens_reading);
            
//        for(int i = 0; i <= 7; i++){
//            seven_seg_set_num(&seven_seg0, i);
//            RGB_LED_Set_Color_Basic(&led0, i);
//            RGB_LED_Update(&led0);
//            
//            for(int j = 32767; j > 0; j--);
//            
//        }
        
        uint8_t high_num = (tmp_sens_trunc % 100) / 10;
        uint8_t low_num  = tmp_sens_trunc % 10;
        
//        uint8_t led_num = (float)(min(max(tmp_sens_trunc + 6, 32), 80) - 32) / 48 * 7;
        uint8_t led_num = min(max(high_num,0),7);
        
        seven_seg_set_num(&seven_seg0, high_num);
        seven_seg_set_num(&seven_seg1, low_num);
        
        RGB_LED_Set_Color_Basic(&led0, led_num);
        
        RGB_LED_Update(&led0);
        RGB_LED_Update(&led1);
        RGB_LED_Update(&led2);
        
        for(int i = 32767; i > 0; i--);
        
    }
}
