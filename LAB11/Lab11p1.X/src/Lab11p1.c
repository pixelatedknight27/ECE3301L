#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include <p18f4620.h>
#include <usart.h>
#include <string.h>

#include "I2C.h"
#include "I2C_Support.h"

#pragma config OSC = INTIO67
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF
//#pragma config CCP2MX = PORTBE

#include "ST7735_TFT.h"
#include "utils.h"
#include "Main_Screen.h"
#include "Interrupt.h"

#define _XTAL_FREQ  8000000             // Set operation for 8 Mhz

char tempSecond = 0xff;
char second = 0x00;
char minute = 0x00;
char hour = 0x00;
char dow = 0x00;
char day = 0x15;
char month = 0x04;
char year = 0x24;
char setup_second, setup_minute, setup_hour, setup_day, setup_month, setup_year;
char alarm_second, alarm_minute, alarm_hour, alarm_date;
char setup_alarm_second, setup_alarm_minute, setup_alarm_hour; 


short Nec_OK = 0;
char Nec_Button;
extern unsigned long long Nec_code;

typedef enum{
    OFF, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE
} colors;

char array1[21] = {0xA2, 0x62, 0xE2, 0x22, 0x02, 0xC2, 0xE0, 0xA8, 0x90, 0x68, 0x98, 0xB0, 0x30, 0x18, 0x7A, 0x10, 0x38, 0x5A, 0x42, 0x4A, 0x52};
char txt1[21][4] = {"CH-\0", " CH\0", "CH+\0", "PRV\0", "NXT\0", "PAU\0", "VL-\0", "VL+\0", " EQ\0", " 0 \0", "100\0", "200\0", " 1 \0", " 2 \0", " 3 \0", " 4 \0", " 5 \0", " 6 \0", " 7 \0", " 8 \0", " 9 \0"};
int color[21] = {RD, RD, RD, CY, CY, GR, BU, BU, MA, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK, BK};
int color2[21] = { RED, RED, RED, CYAN, CYAN, GREEN, BLUE, BLUE, MAGENTA, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE};
int nums[21] = {0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1};

extern volatile unsigned char* RGB_LED[] = {&PORTB, &PORTA, &PORTA};

char off[] = {3, 0, 3};

void main() {
    Init_UART();
    OSCCON = 0x70; // 8 Mhz
    nRBPU = 0; // Enable PORTB internal pull up resistor
    TRISB = 0x01;
    TRISC = 0x00; // PORTC as output
    TRISD = 0x00;
    ADCON1 = 0x0F; //
    TRISA = 0x00;
    TRISE = 0x00;
    
    
    
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
 
    

    Initialize_LCD_Screen();
    
    I2C_Init(100000);
    DS1621_Init();
    DS3231_Setup_Time();
    
    Init_Interrupt();

    // Clear code

    Nec_code = 0x0;

    while (1) {
        
//        signed char tempC = DS1621_Read_Temp();
//        signed char tempF = (tempC * 9 / 5) + 32;
//        printf(" Temperature = %d degreesC = %d degreesF\r\n", tempC, tempF);
//        Wait_One_Sec_Soft();
        
        DS3231_Read_Time();
        if (tempSecond != second) {
            tempSecond = second;
            char tempC = DS1621_Read_Temp();
            char tempF = (tempC * 9 / 5) + 32;
            printf("%02x:%02x:%02x %02x/%02x/%02x", hour, minute, second, month, day, year);
            printf(" Temperature = %d degreesC = %d degreesF\r\n", tempC, tempF);
        }
        
        if (Nec_OK == 1) {
            Nec_OK = 0;
            Enable_INT_Interrupt();
            printf("NEC_Button = %x \r\n", Nec_Button);

            char found = 0xff;

            for (int i = 0; i < 21; i++) {
                if (array1[i] == Nec_Button) {
                    found = i;
                }
            }

            if (found != 0xff) {
                printf("Key Location = %d \r\n\n", found);
                fillCircle(Circle_X, Circle_Y, Circle_Size, color[found]);
                drawCircle(Circle_X, Circle_Y, Circle_Size, ST7735_WHITE);
                drawtext(Text_X, Text_Y, txt1[found], ST7735_WHITE, ST7735_BLACK, TS_1);

                // add code to output color for the RGB LEDS
                
                char LED_Sel = found / 7;
                
                PORTA = 0;
                PORTB = 0;
                PORTCbits.RC0 = nums[found];
                
                
                
                *RGB_LED[LED_Sel] = (*RGB_LED[LED_Sel] & (~0b00000111 << off[LED_Sel])) | ((color2[found] & 0b00000111) << off[LED_Sel]);    
			
                // add code to handle the KEY_PRESSED LED and do the buzzer sound
                PORTDbits.RD7 = 1;
                Activate_Buzzer();
                Wait_One_Sec();
                Deactivate_Buzzer();
                PORTDbits.RD7 = 0;

            }
        }
    }
}


