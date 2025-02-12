  #include <P18F4620.inc>
 config OSC = INTIO67
 config WDT = OFF
 config LVP = OFF
 config BOREN = OFF
Counter_L equ 0x20
Counter_H equ 0x21
Color_Value equ 0x28
Loop_Count equ 0x29
Delay1 equ 0xFF
Delay2 equ 0XF5
 ORG 0x0000
; CODE STARTS FROM THE NEXT LINE
START:
 
 ORG 0x0000
START: 
 MOVLW 0x0F ;
 MOVWF ADCON1 ;
 MOVLW 0x00 ;
 MOVWF TRISC ;  port c set up as output
 MOVLW 0x00
 MOVWF TRISD; port d set up as output
 
 ORG 0x40
 DB 0x05, 0x03, 0x04, 0x06, 0x01, 0x02, 0x07, 0x00
 
 ORG 0x50
 DB 0x30, 0x18, 0x38, 0x00, 0x10, 0x28, 0x20, 0x08
 

WHILE_LOOP: ;
 
 MOVLW 0x08 ;
 MOVWF Loop_Count ; load loop count to 8

 LFSR 0,0x0040
 LFSR 1,0x0050
FOR_LOOP:
 
 MOVF INDF0,W ; change
 MOVWF PORTC ;
 MOVF INDF1,W ; change
 MOVWF PORTD ;
 
 CALL DELAY_ONE_SEC ;;
 INCF FSR0L ;
 INCF FSR1L ;
 
 DECF Loop_Count,F ;
 BNZ FOR_LOOP ;  for loop finished when loop count = 0
 ;
 GOTO WHILE_LOOP ;
; add the code for ?DELAY_ONE_SEC? here
 DELAY_ONE_SEC:
MOVLW Delay1 ;
MOVWF Counter_H ;
LOOP_OUTER:
NOP ;
MOVLW Delay2 ;
MOVWF Counter_L ;
LOOP_INNER:
NOP ;
DECF Counter_L,F ;
BNZ LOOP_INNER ;
DECF Counter_H,F ;
BNZ LOOP_OUTER ;
RETURN
 END 
 
  