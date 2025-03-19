//colors
#define OFF             0               // Defines OFF as decimal value 0
#define RED             1               // Defines RED as decimal value 1
#define GREEN           2               // Defines GREEN as decimal value 2
#define YELLOW          3               // Defines YELLOW as decimal value 3

#define Semester        1               // Type 0 for Sp, 1 for Fa
#define Year            25              // Type 2 digits year
#define Session_Number  1               // Type Session Number 1 through 5
#define Table_Number    03              // Type Table Number from 01 through 14
        

#define EWLT_RED PORTBbits.RB7
#define EWLT_GREEN PORTEbits.RE0

#define EW_RED PORTBbits.RB4
#define EW_GREEN PORTBbits.RB5

#define NSLT_RED PORTCbits.RC2
#define NSLT_GREEN PORTCbits.RC4

#define NS_RED PORTAbits.RA1
#define NS_GREEN PORTAbits.RA2

#define SEC_LED PORTEbits.RE2
#define MODE_LED PORTEbits.RE1

#define SW_EWLT PORTCbits.RC0
#define SW_NSLT PORTAbits.RA5
#define SW_NSPED PORTAbits.RA3
#define SW_EWPED PORTAbits.RA4

#define DP	        PORTDbits.RD7       // Defines Decimal Point as PORTD bit R??

#define mask_TFT	0x70				// mask to protect the TFT signals

#define PEDESTRIAN_NS_WAIT  8
#define NS_WAIT             7
#define EW_LT_WAIT          8
#define PEDESTRIAN_EW_WAIT  7
#define EW_WAIT             6
#define NS_LT_WAIT          7

#define NIGHT_NS_WAIT       6
#define NIGHT_EW_LT_WAIT    7
#define NIGHT_EW_WAIT       6
#define NIGHT_NS_LT_WAIT    8

#define NS 0 // Number definition of North/South
#define NSLT 1 // Number definition of North/South Left Turn
#define EW 2 // Number definition of East/West
#define EWLT 3 // Number definition of East/West Left Turn 

