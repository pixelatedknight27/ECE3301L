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
 * Author: Max Gross (don't change this please, thanks.)
 * Comments:
 * Revision history:
 */

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef XC_HEADER_TEMPLATE_H
#define XC_HEADER_TEMPLATE_H

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

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C
    // linkage so the functions can be used by the c code.

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XC_HEADER_TEMPLATE_H */

/*************************************************************/
/* This driver was built to support full spectrum RGB with   */
/* minimal overhead. R, G, and B values can be set to any    */
/* luminocity between 0 and 255                              */
/*************************************************************/

#include <stdint.h>

typedef struct Pins
{
    volatile unsigned char *port;
    volatile unsigned char *port_dir;
    uint8_t red_pin;
    uint8_t green_pin;
    uint8_t blue_pin;
};

typedef struct Color
{
    uint8_t red_lum;
    uint8_t green_lum;
    uint8_t blue_lum;
};

typedef struct Color_Timer
{
    uint8_t red_ctr;
    uint8_t green_ctr;
    uint8_t blue_ctr;
};

typedef struct RGB_LED
{
    struct Pins pins;
    struct Color color;
    struct Color_Timer color_timer;
};

/*************************************************************/
/* A function to initialize an RGB_LED in main() after       */
/* instantiation. Allows the programmer to declare a port,   */
/* as well as the individual pins of the port used by the    */
/* RGB_LED                                                   */
/*************************************************************/
void RGB_LED_Init(
    struct RGB_LED *LED,
    volatile unsigned char *port,
    volatile unsigned char *port_dir,
    uint8_t red_pin,
    uint8_t green_pin,
    uint8_t blue_pin)
{

    LED->pins.port = port;
    LED->pins.port_dir = port_dir;

    *LED->pins.port_dir = 0x00;
    *LED->pins.port = 0x00;

    // shift 0x01 left by the pin number
    LED->pins.red_pin = 0x01 << red_pin;
    LED->pins.green_pin = 0x01 << green_pin;
    LED->pins.blue_pin = 0x01 << blue_pin;
}

/*************************************************************/
/* Changes the saved color and resets the PWM timer.         */
/* Edits members of the structure, does not effect physical  */
/* hardware.                                                 */
/*************************************************************/
void RGB_LED_Set_Color(struct RGB_LED *LED, uint8_t red, uint8_t green, uint8_t blue)
{
    LED->color.red_lum = red;
    LED->color.green_lum = green;
    LED->color.blue_lum = blue;

    LED->color_timer.red_ctr = 0;
    LED->color_timer.green_ctr = 0;
    LED->color_timer.blue_ctr = 0;
}

/*************************************************************/
/* Update checks if the counter for each color is less than  */
/* the set luminosity and if true, keeps the LED on.         */
/*************************************************************/
void RGB_LED_Update(struct RGB_LED *LED)
{
    uint8_t pin_word = 0b00000000;

    if (LED->color_timer.red_ctr <= LED->color.red_lum)
    {
        //  bitwise or with the pin number to add the pin to the word
        pin_word = pin_word | LED->pins.red_pin;
    }
    if (LED->color_timer.green_ctr <= LED->color.green_lum)
    {
        pin_word = pin_word | LED->pins.green_pin;
    }
    if (LED->color_timer.blue_ctr <= LED->color.blue_lum)
    {
        pin_word = pin_word | LED->pins.blue_pin;
    }

    *LED->pins.port = pin_word;  //  PORTx = pin_word;

    LED->color_timer.red_ctr++;
    LED->color_timer.green_ctr++;
    LED->color_timer.blue_ctr++;
}

typedef enum
{
    OFF,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    CYAN,
    WHITE
} RGB_LED_Colors;

/*************************************************************/
/*  Allows the programmer to pass in preset colors.          */
/*  Can pass in members of the above enum type or raw        */
/*  integers between 0 and 7. The reason I don’t directly    */
/*  change the pin here and instead do it indirectly is to   */
/*  maintain consistency with how RGB_LED_Update() is        */
/*  handled. There should only be one Update and it’s        */
/*   members should always be void.                          */
/*************************************************************/
void RGB_LED_Set_Color_Basic(struct RGB_LED *LED, RGB_LED_Colors color)
{

    if (color == OFF)
    {
        //  the new_color struct is copied into LED->color
        struct Color new_color = {0, 0, 0};
        LED->color = new_color;
    }
    else if (color == RED)
    {
        struct Color new_color = {255, 0, 0};
        LED->color = new_color;
    }
    else if (color == GREEN)
    {
        struct Color new_color = {0, 255, 0};
        LED->color = new_color;
    }
    else if (color == YELLOW)
    {
        struct Color new_color = {255, 255, 0};
        LED->color = new_color;
    }
    else if (color == BLUE)
    {
        struct Color new_color = {0, 0, 255};
        LED->color = new_color;
    }
    else if (color == PURPLE)
    {
        struct Color new_color = {255, 0, 255};
        LED->color = new_color;
    }
    else if (color == CYAN)
    {
        struct Color new_color = {0, 255, 255};
        LED->color = new_color;
    }
    else if (color == WHITE)
    {
        struct Color new_color = {255, 255, 255};
        LED->color = new_color;
    }
    else
    {
        struct Color new_color = {0, 0, 0};
        LED->color = new_color;
    }

    LED->color_timer.red_ctr = 0;
    LED->color_timer.green_ctr = 0;
    LED->color_timer.blue_ctr = 0;
}

/*************************************************************/
/*  Debug                                                    */
/*************************************************************/
void RGB_LED_Print_Status(struct RGB_LED *LED)
{
    printf("RGB vals: %d %d %d\r\n", LED->color.red_lum, LED->color.green_lum, LED->color.blue_lum);
}