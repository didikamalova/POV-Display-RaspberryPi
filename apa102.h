#ifndef APA102_H
#define APA102_H

#include "apa102.h"

/* 
 * Number of frames the strip buffer will contain.
 * Can be smaller than than the number of LEDs 
 * physically available on the strip, but not larger.
 */

#define NUM_LEDS 72

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
 * @param br the brignthess of the LED
 * @param g  the green component of the color
 * @param b  the blue component of the color
 * @param r  the red component of the color
 * 
 * If color parameters are invalid, does nothing.
 */
void apa102_clear(unsigned int br, unsigned char b, unsigned char g, unsigned char r);

/*
 * `apa102_set_led`
 *
 * Sets a single led on the buffer to a certain color.
 *
 * @param n  number of the LED (max = NUM_LEDS-1)
 * @param br the brignthess of the LED (max = 31)
 * @param g  the green component of the color
 * @param b  the blue component of the color
 * @param r  the red component of the color
 * 
 * If n is outside the bounds of the strip or color 
 * parameters are invalid, does nothing.
 */
void apa102_set_led(int n, unsigned int br, unsigned char b, unsigned char g, unsigned char r);

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
