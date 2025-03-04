#include <stdint.h>
#include <usart.h>
#include "RGB_LED.h"

/*************************************************************/
/* This driver was built to support full spectrum RGB with   */
/* minimal overhead. R, G, and B values can be set to any    */
/* luminocity between 0 and 255                              */
/*************************************************************/

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
    uint8_t pin_pos = ~(LED->pins.red_pin | LED->pins.green_pin | LED->pins.blue_pin);
    
    uint8_t pin_word = *LED->pins.port & pin_pos;

    if (LED->color_timer.red_ctr <= LED->color.red_lum & (LED->color.red_lum != 0))
    {
        //  bitwise or with the pin number to add the pin to the word
        pin_word = pin_word | LED->pins.red_pin;
    }
    if (LED->color_timer.green_ctr <= LED->color.green_lum & (LED->color.green_lum != 0))
    {
        pin_word = pin_word | LED->pins.green_pin;
    }
    if (LED->color_timer.blue_ctr <= LED->color.blue_lum & (LED->color.blue_lum != 0))
    {
        pin_word = pin_word | LED->pins.blue_pin;
    }
    
    *LED->pins.port = pin_word;

    LED->color_timer.red_ctr++;
    LED->color_timer.green_ctr++;
    LED->color_timer.blue_ctr++;
}

/*************************************************************/
/*  Allows the programmer to pass in preset colors.          */
/*  Can pass in members of the above enum type or raw        */
/*  integers between 0 and 7. The reason I donâ??t directly    */
/*  change the pin here and instead do it indirectly is to   */
/*  maintain consistency with how RGB_LED_Update() is        */
/*  handled. There should only be one Update and itâ??s        */
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
