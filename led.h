#ifndef LED_H
#define LED_H

#include "spi.h"
#include "uart.h"

/* Some functions we might want to implement */

// initialize the LED strip
void led_init(void);

// clear strip
void clear_strip(void);

// Gets the color and brightness of one pixel in the LED stripe.
void get_pixel(self, led_num);

// Sets the color of one pixel in the LED stripe.
void set_pixel(led_num, red, green, blue, bright_percent);

#endif