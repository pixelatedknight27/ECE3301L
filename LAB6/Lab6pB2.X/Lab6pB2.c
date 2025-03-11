/*
 * File:   Lab6pB2.c
 * Author: maxgr
 *
 * Created on March 4, 2025, 5:51 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include <math.h>
#include <p18f4620.h>

#include "../../Drivers/ADC/ADC.h"
#include "../../Drivers/seven_segment/seven_segment.h"
#include "../../Drivers/UART/UART.h"
#include "../../Drivers/RGB_LED/RGB_LED.h"

#pragma config OSC = INTIO67
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF

void Activate_Buzzer() {
    PR2 = 0b11111001;
    T2CON = 0b00000101;
    CCPR2L = 0b01001010;
    CCP2CON = 0b00111100;
}

void Deactivate_Buzzer() {
    CCP2CON = 0x0;
    PORTCbits.RC1 = 0;
}

struct seven_seg seven_seg0;
struct seven_seg seven_seg1;

struct RGB_LED led0, led1;

void main(void) {
    TRISB = 0x00;

    Init_ADC();

    Init_UART();

    RGB_LED_Init(&led1, &PORTC, &TRISC, 2, 3, 4);
    RGB_LED_Init(&led0, &PORTE, &TRISE, 0, 1, 2);

    seven_seg_init(&seven_seg0, &PORTB, &TRISB);
    seven_seg_init(&seven_seg1, &PORTD, &TRISD);

    for (int j = 8192; j > 0; j--);
    Activate_Buzzer();
    for (int j = 8192; j > 0; j--);
    Deactivate_Buzzer();
    for (int j = 8192; j > 0; j--);

    PORTBbits.RB7 = 0;

    while (1) {
        float adc_reading_0 = Read_Ch_Volt_Converted(3);

        float r_value = adc_reading_0 / (4.096 - adc_reading_0) * 20000 / 1000;
        
        if(r_value > 99){
            r_value = 99;
        }
        
        float r_value_shift = r_value;
        
        printf("r_value:  %fk\r\n", r_value);
        
        uint8_t dp = 0;
        
        if (r_value < 10) {
            dp = 0;
            r_value_shift = r_value_shift * 10;

        } else {
            dp = 1;
        }

        uint8_t r_value_trunc = (uint8_t) (r_value_shift);

        uint8_t high_num = (r_value_trunc % 100) / 10;
        uint8_t low_num = (r_value_trunc % 10);

        seven_seg_set_num(&seven_seg0, high_num, dp);
        seven_seg_set_num(&seven_seg1, low_num, 1);
        
        uint8_t led_num = (uint8_t) (r_value / 10);
        
        if (led_num > 7) {
            led_num = 7;
        }
        
        RGB_LED_Set_Color_Basic(&led0, led_num);

        if (r_value > 0.3) {
            RGB_LED_Set_Color_Basic(&led1, OFF);
                    Deactivate_Buzzer();
        } else if (r_value < 0.3 && r_value > 0.2) {
            RGB_LED_Set_Color_Basic(&led1, RED);
                    Deactivate_Buzzer();
        } else if (r_value < 0.2 && r_value > 0.1) {
            RGB_LED_Set_Color_Basic(&led1, GREEN);
                    Deactivate_Buzzer();
        } else if (r_value < 0.1 && r_value > 0.07) {
            RGB_LED_Set_Color_Basic(&led1, BLUE);
                    Deactivate_Buzzer();
        } else if (r_value < 0.07) {
            RGB_LED_Set_Color_Basic(&led1, WHITE);
                    Activate_Buzzer();
        }  

        RGB_LED_Update(&led1);
        RGB_LED_Update(&led0);

        for (int i = 32767; i > 0; i--);

        }

    return;

}
