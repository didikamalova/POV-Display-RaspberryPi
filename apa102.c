#include "apa102.h"
#include "spi.h"

/* SPI Parameters */
#define POL       0
#define PHA       0
#define CLKDIV 1024


static color_t strip_data[NUM_LEDS];

void apa102_init(void)
{
    spi_init(POL, PHA, CLKDIV);
}

void apa102_clear(color_t c)
{
    printf("%d\n", NUM_LEDS);
    for (int i = 0; i < NUM_LEDS; i++) strip_data[i] = c;
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
    unsigned char end[(NUM_LEDS+15)/16] = { 0 };

    spi_txrx(start, rx, 4);

    for (int i = 0; i < NUM_LEDS; i++) {

        for (int k = 24; k >= 0; k-=8) {
            component = strip_data[i] >> k & 0x0FF;
            spi_txrx(&component, rx, 1);
        }
        
    }
    spi_txrx(end, rx, (NUM_LEDS+15)/16);
}
