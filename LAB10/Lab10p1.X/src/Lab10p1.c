#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include <p18f4620.h>
#include <usart.h>
#include <string.h>

#pragma config OSC = INTIO67
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF
#pragma config CCP2MX = PORTBE

#include "ST7735_TFT.h"
#include "utils.h"
#include "Main_Screen.h"
#include "Interrupt.h"

#define _XTAL_FREQ  8000000             // Set operation for 8 Mhz


short Nec_OK = 0;
char Nec_Button;
extern unsigned long long Nec_code;




char array1[21] = {0xA2, 0x62, 0xE2, 0x22, 0x02, 0xC2, 0xE0, 0xA8, 0x90, 0x68, 0x98, 0xB0, 0x30, 0x18, 0x7A, 0x10, 0x38, 0x5A, 0x42, 0x4A, 0x52};
char txt1[21][4] = {"CH-\0", " CH\0", "CH+\0", "PRV\0", "NXT\0", "PAU\0", "VL-\0", "VL+\0", " EQ\0", " 0 \0", "100\0", "200\0", " 1 \0", " 2 \0", " 3 \0", " 4 \0", " 5 \0", " 6 \0", " 7 \0", " 8 \0", " 9 \0"};
int color[21] = {RD, RD, RD, CY, CY, GR, BU, BU, MA, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK};

void main() {
    Init_UART();
    OSCCON = 0x70; // 8 Mhz
    nRBPU = 0; // Enable PORTB internal pull up resistor
    TRISB = 0x01;
    TRISC = 0x00; // PORTC as output
    TRISD = 0x00;
    ADCON1 = 0x0F; //
    TRISE = 0x00;

    Initialize_LCD_Screen();
    Init_Interrupt();

    // Clear code

    Nec_code = 0x0;

    while (1) {
        if (Nec_OK == 1) {
            Nec_OK = 0;
            Enable_INT_Interrupt();
            printf("NEC_Button = %x \r\n", Nec_Button);

            char found = 0xff;

            // add code here to look for code using a FOR loop

            if (found != 0xff) {
                printf("Key Location = %d \r\n\n", found);
                fillCircle(Circle_X, Circle_Y, Circle_Size, color[found]);
                drawCircle(Circle_X, Circle_Y, Circle_Size, ST7735_WHITE);
                drawtext(Text_X, Text_Y, txt1[found], ST7735_WHITE, ST7735_BLACK, TS_1);

                // add code to output color for the RGB LEDS

                // add code to handle the KEY_PRESSED LED and do the buzzer sound

            }
        }
    }
}


