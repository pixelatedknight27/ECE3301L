#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include <p18f4620.h>

#include "../../../Drivers/seven_segment/seven_segment.h"
#inculde "../../../Drivers/RGB_LED/RGB_LED.h"

#pragma config OSC = INTIO67
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF
#define delay 5

struct seven_seg seven_seg0;

int coutner1;

void main(void) {
    
    seven_seg_init(&seven_seg0, &PORTD, &TRISD);
    seven_seg_set_num(&seven_seg0, 3);
    
    while (1) {
        
        for(int i = 0; i <= 9; i++){
            seven_seg_set_num(&seven_seg0, i);
            
            for(int j = 8192; j > 0; j--);
            
        }
    }
}