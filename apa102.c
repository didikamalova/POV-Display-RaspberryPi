#include "apa102.h"
#include "spi.h"
#include "printf.h"

/* SPI Parameters */
#define POL       0
#define PHA       0
#define CLKDIV 1024

/* 
 * Number of frames the strip buffer will contain.
 * Can be smaller than than the number of LEDs 
 * physically available on the strip, but not larger.
 */

#define NUM_LEDS 60

static color_t strip_data[NUM_LEDS] = { 0 };

void apa102_init(void)
{
    spi_init(POL, PHA, CLKDIV);
    for (int i = 0; i < NUM_LEDS; i++) strip_data[i] = 0;
}

void apa102_clear(color_t c)
{
    for (int i = 0; i < NUM_LEDS; i++) strip_data[i] = c;

    //for (int i = 0; i < NUM_LEDS; i++) printf("LED: %d, %x\n", i, strip_data[i]);
}

void apa102_set_led(int n, color_t c)
{
    if (n < 0 || n >= NUM_LEDS) return;
    strip_data[n] = c;
}


void apa102_show(void)
{
    int frame_len = (NUM_LEDS+1)*4 + (NUM_LEDS+15)/16;
    unsigned char rx[frame_len];
    unsigned char component;

    unsigned char start[4] = { 0 };
    //int end_len = (NUM_LEDS+15)/16;
    unsigned char end[4] = { 0 };

    spi_txrx(start, rx, 4);
    //printf("\n");
    for (int i = 0; i < NUM_LEDS; i++) {
        //printf("LED: %d, %x\n", i, strip_data[i]);
        for (int k = 24; k >= 0; k-=8) {
            component = strip_data[i] >> k & 0x0FF;
            spi_txrx(&component, rx, 1);
        }
    }

    spi_txrx(end, rx, 4);
}
