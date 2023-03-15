#include "apa102.h"
#include "spi.h"

/* SPI Parameters */
#define POL       0
#define PHA       0
#define CLKDIV 1024

typedef struct BRGB {
    unsigned char brightness;
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} BRGB;

static struct BRGB strip_data[NUM_LEDS];

void apa102_init(void)
{
    spi_init(POL, PHA, CLKDIV);
}

void apa102_clear(unsigned int br, unsigned char b, unsigned char g, unsigned char r)
{
    for (int i = 0; i < NUM_LEDS; i++) {
        strip_data[i].brightness = br;
        strip_data[i].red = r;
        strip_data[i].green = g;
        strip_data[i].blue = b;
    }
}

void apa102_set_led(int n, unsigned int br, unsigned char b, unsigned char g, unsigned char r)
{
    strip_data[n].red = r;
    strip_data[n].green = g;
    strip_data[n].blue = b;
    strip_data[n].brightness = br;
}

void apa102_show(void)
{
    int frame_len = (NUM_LEDS+1)*4 + (NUM_LEDS+15)/16;
    unsigned char rx[frame_len];

    unsigned char start[4] = { 0 };
    unsigned char end[(NUM_LEDS+15)/16] = { 0 };

    spi_txrx(start, rx, 4);

    for (int i = 0; i < NUM_LEDS; i++) {
        spi_txrx(&strip_data[i].brightness, rx, 1);
        spi_txrx(&strip_data[i].blue, rx, 1);
        spi_txrx(&strip_data[i].green, rx, 1);
        spi_txrx(&strip_data[i].red, rx, 1);
    }

    spi_txrx(end, rx, (NUM_LEDS+15)/16);
}
