#include "ADC.h"

void Init_ADC(int ch_sel) {
    ADCON0 = 0x01; // select channel AN0, and turn on the ADDC subsystem
    ADCON1 = ch_sel; // 0x1b = set pins 2,3,4,5 & 7 as analog signal, VDD-VSS as ref voltage
    ADCON2 = 0xA9; // Set the bit conversion time (TAD) and acquisition time
}

unsigned int Get_Full_ADC(void) {
    int result;
    ADCON0bits.GO = 1; // Start Conversion
    while (ADCON0bits.DONE == 1); // Wait for conversion to be completed (DONE=0)
    result = (ADRESH * 0x100) + ADRESL; // Combine result of upper byte and lower byte into
    return result; // return the most significant 8- bits of the result.
}

float Read_Ch_Volt(char ch_num) {
    
    // returns a float between 0 and 1023
    
    ADCON0 = ch_num * 0x4 + 1;
    int ADC_Result = Get_Full_ADC();
    float Volt = ADC_Result;
    return (Volt);
}

float Read_Ch_Volt_Converted(char ch_num) {
    
    // returns a voltage between 0 and 5
    
    ADCON0 = ch_num * 0x4 + 1;
    float ADC_Result = Get_Full_ADC();
//    float Volt = 4.0 * ADC_Result / 1000.0;
    float Volt = 5 * ADC_Result / 1024;
    return (Volt);
}