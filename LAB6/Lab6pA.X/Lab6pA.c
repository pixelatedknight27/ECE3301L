/*
 * File:   Lab6p1.c
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

void main(void) {
    TRISC = 0x00;
    
    Init_ADC();
    
    Init_UART();
    
    seven_seg_init(&seven_seg0, &PORTB, &TRISB);
    seven_seg_init(&seven_seg1, &PORTD, &TRISD);
    
    for(int j = 8192; j > 0; j--);
    Activate_Buzzer();
    for(int j = 8192; j > 0; j--);
    Deactivate_Buzzer();
    for(int j = 8192; j > 0; j--);
    
    PORTBbits.RB7 = 0;
    
    while(1){
        float adc_reading_0 = Read_Ch_Volt_Converted(0);
        
        uint8_t adc_reading_trunc_0 = (uint8_t) (adc_reading_0 * 10);

        printf("voltage: %f\r\n", adc_reading_0);

        uint8_t high_num = (adc_reading_trunc_0 % 100) / 10;
        uint8_t low_num = adc_reading_trunc_0 % 10;
        
        seven_seg_set_num(&seven_seg0, high_num, 0);
        seven_seg_set_num(&seven_seg1, low_num, 1);
    }
    
    return;
    
    
}
