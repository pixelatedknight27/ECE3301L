#include "Buzzer.h"

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
