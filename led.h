#ifndef LED_H
#define LED_H

#include "spi.h"
#include "uart.h"

#define NUM_LEDS 6 // number of LEDs

/* Some functions we might want to implement */

// initialize the LED strip
void led_init(void);

// sets the color of one pixel in the LED stripe.
void set_pixel(int pixel, unsigned char r, unsigned char g, unsigned char b);

// diplays the led frame contents
void led_show(void);

// gets the color and brightness of one pixel in the LED stripe.
void get_pixel(int pixel);

// clear strip and set every led to one color
void clear_strip(unsigned int r, unsigned int g, unsigned int b);

#endif