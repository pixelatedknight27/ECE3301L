//colors
#define OFF             0               // Defines OFF as decimal value 0
#define RED             1               // Defines RED as decimal value 1
#define GREEN           2               // Defines GREEN as decimal value 2
#define YELLOW          3               // Defines YELLOW as decimal value 3

#define Semester        0               // Type 0 for Sp, 1 for Fa
#define Year            24              // Type 2 digits year
#define Session_Number  1               // Type Session Number 1 through 5
#define Table_Number    01              // Type Table Number from 01 through 14
        

#define EW_RED      PORTBbits.RB4       // Defines EW_RED as PORT? bit R??
#define EW_GREEN    PORTBbits.RB5       // Defines EW_GREEN as PORT? bit R??

#define EWLT_RED    PORTBbits.RB7       // Defines EWLT_RED as PORT? bit R??
#define EWLT_GREEN  PORTEbits.RE0       // Defines EWLT_GREEN as PORT? bit R??

#define NS_RED      PORTAbits.RA1       // Defines NS_RED as PORT? bits R??
#define NS_GREEN    PORTAbits.RA2       // Defines NS_GREEN as PORT? bit R??

#define NSLT_RED    PORTCbits.RC2       // Defines NS_LT RED as PORT? bit R??
#define NSLT_GREEN  PORTCbits.RC4       // Defines NS_LT GREEN as PORT? bit R??

#define EW_LT_SW    PORTCbits.RC0       // Defines EW_PED as PORT? bit R?? for left turn
//#define EW_PED_SW   PORTAbits.RA4       // Defines NS_PED as PORT? bit R?? for Ped-switch
#define NS_LT_SW    PORTAbits.RA5       // Defines NS_LT as PORT? bit R?? for left turn
//#define NS_PED_SW   PORTAbits.RA3       // Defines EW_LT as PORT? bit R?? for Ped-switch

#define MODE_LED    PORTEbits.RE1       // Defines MODE_LED as PORT? bit R?? to differentiate day/night mode
#define SEC_LED     PORTEbits.RE2       // Defines SEC_LED as PORT? bit R??

#define DP	        PORTDbits.RD7       // Defines Decimal Point as PORTD bit R??

#define mask_TFT	0b01110000				// mask to protect the TFT signals

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

