
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include <p18f4620.h>
#include "../../Drivers/Buzzer/Buzzer.h"
#include "../../Drivers/ADC/ADC.h"
#include "../../Drivers/seven_segment/seven_segment.h"
#pragma config OSC = INTIO67
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF

#define EWLT_RED PORTBbits.RB7
#define EWLT_GREEN PORTEbits.RE0

#define EW_RED PORTCbits.RC4
#define EW_GREEN PORTCbits.RC5

#define NSLT_RED PORTCbits.RC2
#define NSLT_GREEN PORTCbits.RC3

#define NS_RED PORTAbits.RA1
#define NS_GREEN PORTAbits.RA2

#define SEC_LED PORTEbits.RE2
#define MODE_LED PORTEbits.RE1

#define OFF 0
#define RED 1
#define GREEN 2
#define YELLOW 3

// Prototype Area

void Init_UART(void);
void putch(char c);
float Read_Ch_Volt(char);

void Print(int v, int F, int photo);
void Wait_One_Second_With_Beep();

struct seven_seg seven_seg0;
struct seven_seg seven_seg1;


void Wait_N_Seconds(char seconds);
void Wait_One_Second();
void Wait_Half_Second();

void Set_NS(char color);
void Set_NSLT(char color);
void Set_EW(char color);
void Set_EWLT(char color);

void PED_Control(char Direction, char Num_Sec);

char LED_7seg[10] = {0x01, 0x4F, 0x12, 0x06, 0x4C, 0x24, 0x20, 0x0F, 0x00, 0x0C};

void main(void) {
    Init_ADC(0x0F);
    Init_UART();

    TRISA = 0xF9;
    ADCON1 = 0x0E;
    OSCCON = 0x70;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    seven_seg_init(&seven_seg0, &PORTB, &TRISB);
    seven_seg_init(&seven_seg1, &PORTD, &TRISD);
    while (1) {


        PED_Control(0, 8); // Set direction 0 and do for 8 seconds
        PED_Control(1, 6); // Set direction 1 for 6 seconds 




    }
}

void PED_Control(char Direction, char Num_Sec) {
    if (Direction == 0) {

        seven_seg_set_num(&seven_seg1, -1);

        for (int i = Num_Sec-1; i > 0; i--) {

            seven_seg_set_num(&seven_seg0, i);
            Wait_One_Second_With_Beep();
            if (i == 1) {
                seven_seg_set_num(&seven_seg0, -1);
                Wait_One_Second_With_Beep();
            }
        }
    } else {
        seven_seg_set_num(&seven_seg0, -1);

        for (int i = Num_Sec-1; i > 0; i--) {
            seven_seg_set_num(&seven_seg1, i);
            Wait_One_Second_With_Beep();
            if (i == 1) {
                seven_seg_set_num(&seven_seg1, -1);
                Wait_One_Second_With_Beep();
            }
        }
    }
}

void Wait_One_Second_With_Beep() {
    SEC_LED = 1; // First, turn on the SEC LED
    Activate_Buzzer(); // Activate the buzzer
    Wait_Half_Second(); // Wait for half second (or 500 msec)
    SEC_LED = 0; // then turn off the SEC LED
    Deactivate_Buzzer(); // Deactivate the buzzer
    Wait_Half_Second(); // Wait for half second (or 500 msec)
}

void Set_NS(char color) {
    switch (color) {
        case OFF: NS_RED = 0;
            NS_GREEN = 0;
            break; // Turns off the NS LED
        case RED: NS_RED = 1;
            NS_GREEN = 0;
            break; // Sets NS LED RED
        case GREEN: NS_RED = 0;
            NS_GREEN = 1;
            break; // sets NS LED GREEN
        case YELLOW: NS_RED = 1;
            NS_GREEN = 1;
            break; // sets NS LED YELLOW
    }
}

void Set_NSLT(char color) {
    switch (color) {
        case OFF: NSLT_RED = 0;
            NSLT_GREEN = 0;
            break; // Turns off the NS LED
        case RED: NSLT_RED = 1;
            NSLT_GREEN = 0;
            break; // Sets NS LED RED
        case GREEN: NSLT_RED = 0;
            NSLT_GREEN = 1;
            break; // sets NS LED GREEN
        case YELLOW: NSLT_RED = 1;
            NSLT_GREEN = 1;
            break; // sets NS LED YELLOW
    }
}

void Set_EW(char color) {
    switch (color) {
        case OFF: EW_RED = 0;
            EW_GREEN = 0;
            break; // Turns off the NS LED
        case RED: EW_RED = 1;
            EW_GREEN = 0;
            break; // Sets NS LED RED
        case GREEN: EW_RED = 0;
            EW_GREEN = 1;
            break; // sets NS LED GREEN
        case YELLOW: EW_RED = 1;
            EW_GREEN = 1;
            break; // sets NS LED YELLOW
    }
}

void Set_EWLT(char color) {
    switch (color) {
        case OFF: EWLT_RED = 0;
            EWLT_GREEN = 0;
            break; // Turns off the NS LED
        case RED: EWLT_RED = 1;
            EWLT_GREEN = 0;
            break; // Sets NS LED RED
        case GREEN: EWLT_RED = 0;
            EWLT_GREEN = 1;
            break; // sets NS LED GREEN
        case YELLOW: EWLT_RED = 1;
            EWLT_GREEN = 1;
            break; // sets NS LED YELLOW
    }
}

void Wait_N_Seconds(char seconds) {
    char I;
    for (I = 0; I < seconds; I++) {
        Wait_One_Second();
    }
}

void Wait_One_Second() {
    SEC_LED = 1; // First, turn on the SEC LED
    Wait_Half_Second(); // Wait for half second (or 500 msec)
    SEC_LED = 0; // then turn off the SEC LED
    Wait_Half_Second(); // Wait for half second (or 500 msec)
}

void Wait_Half_Second() {
    T0CON = 0x03; // Timer 0, 16-bit mode, prescaler 1:16
    TMR0L = 0xBF; // set the lower byte of TMR
    TMR0H = 0x09; // set the upper byte of TMR
    INTCONbits.TMR0IF = 0; // clear the Timer 0 flag
    T0CONbits.TMR0ON = 1; // Turn on the Timer 0
    while (INTCONbits.TMR0IF == 0); // wait for the Timer Flag to be 1 for done
    T0CONbits.TMR0ON = 0; // turn off the Timer 0
}

/*void Print(int v, int F, int photo) {
    printf("\nVoltage = %d [mV]\r\n", v);
    printf("Temperature = %d [F]\r\n", F);
    printf("PhotoResistor = %d [mV]\r\n", photo);
}
 */
void Init_UART() {
    OpenUSART(USART_TX_INT_OFF & USART_RX_INT_OFF &
            USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX &
            USART_BRGH_HIGH, 25);
    OSCCON = 0x70;
}

void NightMode() {
    Set_EW(RED);
    Set_EWLT(RED);
    Set_NSLT(RED);
    Set_NS(GREEN);
}



