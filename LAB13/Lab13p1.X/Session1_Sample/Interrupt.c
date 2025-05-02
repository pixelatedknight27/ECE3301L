#include <xc.h>
#include <p18f4620.h>
#include "Interrupt.h"
#include "stdio.h"


unsigned char bit_count;
unsigned int Time_Elapsed;

extern unsigned char Nec_state;
extern short Nec_OK;
unsigned long long Nec_code;

extern char Nec_Button;
extern char INT0_flag;
extern char INT1_flag;
extern char INT2_flag;

void Init_Interrupt(void) {
    // put the code to initialize the INT0, INT1, INT2 
    INTCONbits.INT0IF = 0; // interrupts
    INTCON3bits.INT1IF = 0;
    INTCON3bits.INT2IF = 0;

    INTCONbits.INT0IE = 1;
    INTCON3bits.INT1IE = 1;
    INTCON3bits.INT2IE = 1;

    INTCON2bits.INTEDG0 = 0;
    INTCON2bits.INTEDG1 = 0;
    INTCON2bits.INTEDG2 = 0;
    TMR1H = 0; // Reset Timer1
    TMR1L = 0; //
    PIR1bits.TMR1IF = 0; // Clear timer 1 interrupt flag
    PIE1bits.TMR1IE = 1; // Enable Timer 1 interrupt
    INTCONbits.PEIE = 1; // Enable Peripheral interrupt
    INTCONbits.GIE = 1; // Enable global interrupts

}

void interrupt high_priority chkisr() {
    if (PIR1bits.TMR1IF == 1) TIMER1_isr();
    if (INTCONbits.INT0IF == 1) INT0_isr(); // check the INT0 interrupt
    if (INTCON3bits.INT1IF == 1) INT1_isr(); // check the INT1 interrupt
    if (INTCON3bits.INT2IF == 1) INT2_isr(); // check the INT2 interrupt
}

void TIMER1_isr(void) {
    Nec_state = 0; // Reset decoding process
    INTCON2bits.INTEDG1 = 0; // Edge programming for INT0 falling edge
    T1CONbits.TMR1ON = 0; // Disable T1 Timer
    PIR1bits.TMR1IF = 0; // Clear interrupt flag
}

void force_nec_state0() {
    Nec_state = 0;
    T1CONbits.TMR1ON = 0;
}

void INT1_isr() {
    INTCONbits.INT0IF = 0; // Clear external interrupt INT0IF
    if (Nec_state != 0) {
        Time_Elapsed = (TMR1H << 8) | TMR1L; // Store Timer1 value
        TMR1H = 0; // Reset Timer1
        TMR1L = 0;
    }

    switch (Nec_state) {
        case 0:
        {
            // Clear Timer 1
            TMR1H = 0; // Reset Timer1
            TMR1L = 0; //
            PIR1bits.TMR1IF = 0; //
            T1CON = 0x90; // Program Timer1 mode with count = 1usec using System clock running at 8Mhz
            T1CONbits.TMR1ON = 1; // Enable Timer 1
            bit_count = 0; // Force bit count (bit_count) to 0
            Nec_code = 0; // Set Nec_code = 0
            Nec_state = 1; // Set Nec_State to state 1
            PORTE = (PORTE & (0xF8)) | (Nec_state & (0x07));

            INTCON2bits.INTEDG0 = 1; // Change Edge interrupt of INT 0 to Low to High    

            return;
        }

        case 1:
        {
            if (Time_Elapsed >= 8500 && Time_Elapsed <= 9500) {
                Nec_state = 2;

                PORTE = (PORTE & (0xF8)) | (Nec_state & (0x07));

            } else {
                Reset_Nec_state();
            }

            INTCON2bits.INTEDG0 = 0; // Change Edge interrupt of INT 0 to High to Low

            return;
        }

        case 2: // Add your code here
        {
            if (Time_Elapsed >= 4000 && Time_Elapsed <= 5000) {
                Nec_state = 3;

                PORTE = (PORTE & (0xF8)) | (Nec_state & (0x07));

            } else {
                Reset_Nec_state();
            }

            INTCON2bits.INTEDG0 = 1; // Change Edge interrupt of INT 0 to Low to High

            return;
        }

        case 3: // Add your code here
        {
            if (Time_Elapsed >= 400 && Time_Elapsed <= 700) {
                Nec_state = 4;

                PORTE = (PORTE & (0xF8)) | (Nec_state & (0x07));

            } else {
                Reset_Nec_State();
            }

            INTCON2bits.INTEDG0 = 0; // Change Edge interrupt of INT 0 to High to Low

            return;
        }

        case 4: // Add your code here
        {
            if (Time_Elapsed >= 400 && Time_Elapsed <= 1800) {

                Nec_code = Nec_code << 1;

                Time_Elapsed > 1000 ? Nec_code++ : 0;

                bit_count++;

                if (bit_count > 31) {
                    Nec_Button = Nec_code >> 8;
                    Nec_state = 0;

                    PORTE = (PORTE & (0xF8)) | (Nec_state & (0x07));

                    Nec_OK = 1;

                    INT0IE = 0;
                } else {
                    Nec_state = 3;

                    PORTE = (PORTE & (0xF8)) | (Nec_state & (0x07));
                }

            }

            else {
                Reset_Nec_State();
            }

            INTCON2bits.INTEDG0 = 1; // Change Edge interrupt of INT 0 to Low to High

            return;
        }
    }
    // put your code from your IR lab here

}

void INT0_isr() {
    int k;
    for (k = 0; k < 20000; k++);
    INTCONbits.INT0IF = 0;
    INT0_flag = 1;
}

void INT2_isr() {
    int k;
    for (k = 0; k < 20000; k++);
    INTCON3bits.INT2IF == 0;
    INT2_flag = 1;

}





