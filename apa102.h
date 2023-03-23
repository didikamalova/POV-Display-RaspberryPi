#ifndef APA102_H
#define APA102_H

#include "apa102.h"

/* 
 * Number of frames the strip buffer will contain.
 * Can be smaller than than the number of LEDs 
 * physically available on the strip, but not larger.
 */

#define NUM_LEDS 120

/*
 * `color_t`
 *
 * ABGR colors, where each color component B, G, R, or A is a single 
 * unsigned byte. The least signficant byte is the R component, and A 
 * is most significant. In this setting, the brightness maximum (31).
 */
typedef unsigned int color_t;

/* Common Colors */
#define WHITE    0xFFFFFFFF
#define RED      0xFF0000FF
#define GREEN    0xFF00FF00
#define BLUE     0xFFFF0000

/*
 * `apa102_init`
 *
 * Initializes the SPI connection with the Pi.
 */
void apa102_init(void);

/*
 * `apa102_clear`
 *
 * Clears all the LEDs in the buffer to the given color.
 *
 * @param c color
 * 
 * If color parameters are invalid, does nothing.
 */
void apa102_clear(color_t c);

/*
 * `apa102_set_led`
 *
 * Sets a single led on the buffer to a certain color.
 *
 * @param c color
 * 
 * If n is outside the bounds of the strip or color 
 * parameters are invalid, does nothing.
 */
void apa102_set_led(int n, color_t c);

/*
 * `apa102_show`
 *
 * Displays the contents of the buffer on the strip.
 */
void apa102_show(void);

/*
 * `apa102_get_led`
 *
 * Returns the color of a single LED on the strip.
 *
 * @param n  number of the LED (between 0 and NUM_LEDS-1)
 *
 * If n is outside the bounds of the strip, does nothing.
 */
void apa102_get_led(int n);

#endif
