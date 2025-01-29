/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

struct Pins {
    volatile unsigned char *port;
    uint8_t red_pin;
    uint8_t green_pin;
    uint8_t blue_pin;
};

struct Color {
    uint8_t red_lum;
    uint8_t green_lum;
    uint8_t blue_lum;
    
};

struct Color_Timer{
    uint8_t red_ctr;
    uint8_t green_ctr;
    uint8_t blue_ctr;
};

struct RGB_LED {
    struct Pins pins;
    struct Color color;
    struct Color_Timer color_timer;
};

void RGB_LED_Init(
        struct RGB_LED *LED,
        unsigned char *port,
        uint8_t red_pin,
        uint8_t green_pin,
        uint8_t blue_pin) {
    LED->pins.port = port;
    LED->pins.red_pin = 0x01 << red_pin;
    LED->pins.green_pin = 0x01 << green_pin;
    LED->pins.blue_pin = 0x01 << blue_pin;
}

void RGB_LED_Set_Color(struct RGB_LED *LED, uint8_t red, uint8_t green, uint8_t blue){
    LED->color.red_lum = red;
    LED->color.green_lum = green;
    LED->color.blue_lum = blue;
    
    LED->color_timer.red_ctr = 0;
    LED->color_timer.green_ctr = 0;
    LED->color_timer.blue_ctr = 0;
}

void RGB_LED_Update(struct RGB_LED *LED){
    uint8_t pin_word = 0b00000000;
    
    if (LED->color_timer.red_ctr < LED->color.red_lum){
        pin_word = pin_word | LED->pins.red_pin;
    }
    if (LED->color_timer.green_ctr < LED->color.green_lum){
        pin_word = pin_word | LED->pins.green_pin;
    }
    if (LED->color_timer.blue_ctr < LED->color.blue_lum){
        pin_word = pin_word | LED->pins.blue_pin;
    }
    
//    LATB = pin_word;
    *LED->pins.port = pin_word;
    
    LED->color_timer.red_ctr ++;
    LED->color_timer.green_ctr ++;
    LED->color_timer.blue_ctr ++;
}

void RGB_LED_Print_Status(struct RGB_LED *LED){
    printf("LED ctrs: %d %d %d\r\n", LED->color.red_lum, LED->color.green_lum,LED->color.blue_lum);
}