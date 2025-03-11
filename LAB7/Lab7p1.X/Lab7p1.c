
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include <p18f4620.h>

#pragma config OSC = INTIO67
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF

#define SEC_LED PORTEbits.RE2

void Wait_N_Seconds(char seconds);
void Wait_One_Second();
void Wait_Half_Second();

void main(void) {
    OSCCON = 0x70;
    TRISE = 0x00;
    while (1) {
        Wait_One_Second(); // call Wait-N-Second routine to wait for 1 second
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