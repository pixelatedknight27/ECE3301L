
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include <p18f4620.h>

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

#define OFF 0
#define RED 1
#define GREEN 2
#define YELLOW 3

// Prototype Area
void Init_ADC(void);
unsigned int get_full_ADC(void);
void Init_UART(void);
void putch(char c);
float Read_Ch_Volt(char);
void Set_ADCON0(char AN_pin);
void Print(int v, int F, int photo);


void Wait_N_Seconds(char seconds);
void Wait_One_Second();
void Wait_Half_Second();

void Set_NS(char color);
void Set_NSLT(char color);
void Set_EW(char color);
void Set_EWLT(char color);

void PED_Control( char Direction, char Num_Sec);

void main(void) {
    
    Init_UART();

    TRISA = 0xF9;
    ADCON1 = 0x0E;
    OSCCON = 0x70;

    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    while (1) {
        

        char LED_7seg[10] = {0x01, 0x4F, 0x12, 0x06, 0x4C, 0x24, 0x20, 0x0F, 0x00, 0x0C};


        for (int i = 0; i < 4; i++) {
            Set_NS(i); // Set color for North-South direction
            Set_NSLT(i); // Set color for North-South Left-Turn direction
            Set_EW(i); // Set color for East-West direction
            Set_EWLT(i); // Set color for East-West Left-Turn direction
            Wait_N_Seconds(1); // call Wait-N-Second routine to wait for 1 second
        }

    }
}
void PED_Control( char Direction, char Num_Sec)
{
   // if(direction ==0)
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





