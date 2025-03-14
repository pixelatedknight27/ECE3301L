; THIS FIRST ASSEMBLY LANGUAGE PROGRAM WILL FLASH LEDS
; CONNECTED TO THE PINS 0 THROUGH 3 OF PORT B
#include<P18F4620.inc>
    config OSC = INTIO67
    config WDT = OFF
    config LVP = OFF
    config BOREN = OFF
    
; Constant declarations
Delay1 equ 0xFF
Delay2 equ 0XF5
Counter_L equ 0x20
Counter_H equ 0x21
 
    ORG 0x0000
; CODE STARTS FROM THE NEXT LINE
START:
    MOVLW 0x0F		;
    MOVWF ADCON1	;
    MOVLW 0x00		;
    MOVWF TRISB		;
    MOVWF TRISD		;
MAIN_LOOP:
    MOVLW 0x05		;
    MOVWF PORTB		;
    MOVWF PORTD		;
			;
    CALL DELAY_ONE_SEC	;
    MOVLW 0x0A		;
    MOVWF PORTB		;
    MOVWF PORTD		;
    CALL DELAY_ONE_SEC	;
    GOTO MAIN_LOOP	;
    
; the routine below is a subroutine and it is called ?DELAY_ONE_SEC?.
DELAY_ONE_SEC:
    MOVLW Delay1	;
    MOVWF Counter_H	;
    
LOOP_OUTER:
    NOP			;
    MOVLW Delay2	;
    MOVWF Counter_L	;
    
LOOP_INNER:
    NOP			;
    DECF Counter_L,F	;
    BNZ LOOP_INNER	;
    DECF Counter_H,F	;
    BNZ LOOP_OUTER	;
    RETURN
; end of subroutine ?DELAY_ONE_SEC?
END