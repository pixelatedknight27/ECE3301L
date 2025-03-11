/*
 * File:   Lab7p1.c
 * Author: maxgr
 *
 * Created on March 11, 2025, 5:51 AM
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
#include "../../Drivers/Buzzer/Buzzer.h"

#pragma config OSC = INTIO67
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF

struct seven_seg seven_seg0;
struct seven_seg seven_seg1;

void main(void) {
    
    TRISA = 0b00111001;
    TRISC = 0x01;
    PORTC = 0x00;
    TRISE = 0x00;
    
    Init_ADC(0x0E);
    
    Init_UART();
    
    seven_seg_init(&seven_seg0, &PORTB, &TRISB);
    seven_seg_init(&seven_seg1, &PORTD, &TRISD);
    
    for(int j = 8192; j > 0; j--);
    Activate_Buzzer();
    for(int j = 8192; j > 0; j--);
    Deactivate_Buzzer();
    for(int j = 8192; j > 0; j--);
    
    while(1){
        float adc_reading_0 = Read_Ch_Volt_Converted(0);
        
        uint8_t adc_reading_trunc_0 = (uint8_t) (adc_reading_0 * 10);

        printf("voltage: %f\r\n", adc_reading_0);

        uint8_t high_num = (adc_reading_trunc_0 % 100) / 10;
        uint8_t low_num = adc_reading_trunc_0 % 10;
        
        seven_seg_set_num_dp(&seven_seg0, high_num, 0);
        seven_seg_set_num_dp(&seven_seg1, low_num, 1);
        
        PORTCbits.RC2 = PORTAbits.RA3;
        PORTCbits.RC3 = PORTAbits.RA4;
        PORTCbits.RC4 = PORTAbits.RA5;
        PORTCbits.RC5 = PORTCbits.RC0;
        
        PORTAbits.RA1 = PORTAbits.RA3;
        PORTAbits.RA2 = PORTAbits.RA4;
        PORTBbits.RB7 = PORTAbits.RA5;
        PORTEbits.RE0 = PORTCbits.RC0;
        
        PORTEbits.RE1 = PORTAbits.RA3;
        PORTEbits.RE2 = PORTAbits.RA4;
        
//        for (int i = 32767; i > 0; i--);
    }
    
    return;
    
    
}
