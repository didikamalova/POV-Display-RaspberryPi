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
 * `color_t`
 *
 * BGRA colors, where each color component B, G, R, or A is a single 
 * unsigned byte. The least signficant byte is the B component, and A 
 * is most significant.
 */
typedef unsigned int color_t;

/* Common Colors */
#define BLACK    0xFF000000
#define WHITE    0xFFFFFFFF
#define RED      0xFFFF0000
#define GREEN    0xFF00FF00
#define BLUE     0xFF0000FF
#define CYAN     0xFF00FFFF
#define MAGENTA  0xFFFF00FF
#define YELLOW   0xFFFFFF00
#define AMBER    0xFFFFBF00
#define ORANGE   0xFFFF3F00
#define PURPLE   0xFF7F00FF
#define INDIGO   0xFF000040
#define CAYENNE  0xFF400000
#define MOSS     0xFF004000
#define SILVER   0xFFBBBBBB


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
