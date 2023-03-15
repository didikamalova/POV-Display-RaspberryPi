#include "spi.h"
#include "led.h"
#include "uart.h"
#include "strings.h"

/*
APA102 Protocol:
1. Send 32 bits of zeros to update the frame.
2. Send color information regarding each of the LEDs.
3. Finish off by cycling the clock line a few times to get all data to the very last LED on the strip
*/

// SPI parameters
#define POL     0
#define PHA     0
#define CLKDIV 2000

typedef struct BRGB {
    unsigned char brightness;
    unsigned char blue;
    unsigned char green;
    unsigned char red;   
} BRGB;

struct BRGB led_data[NUM_LEDS];

void led_init(void)
{
    spi_init(POL, PHA, CLKDIV);
}

void set_pixel(int pixel, unsigned char r, unsigned char g, unsigned char b)
{
    led_data[pixel].red = r;
    led_data[pixel].green = g;
    led_data[pixel].blue = b;
    led_data[pixel].brightness = 31;
}

void clear_strip(unsigned int r, unsigned int g, unsigned int b)
{
    for (int i = 0; i < NUM_LEDS; i++) {
        led_data[i].brightness = 255;
        led_data[i].red = r;
        led_data[i].green = g;
        led_data[i].blue = b;
    }
}

void led_show(void)
{
    unsigned char start_frame[4] = {0}; // 4 bytes of 0's
    unsigned char end_frame[(NUM_LEDS+15)/16] = {0};

    unsigned char temp = {0xFF};

    int overall = (NUM_LEDS+1)*4 + (NUM_LEDS+15)/16;
    unsigned char rx[overall];

    spi_txrx(start_frame, rx, 4);

    for (int i = 0; i < NUM_LEDS; i++) {
        spi_txrx(&led_data[i].brightness, rx, 1);
        spi_txrx(&led_data[i].blue, rx, 1);
        spi_txrx(&led_data[i].green, rx, 1);
        spi_txrx(&led_data[i].red, rx, 1);
    }

    spi_txrx(end_frame, rx, (NUM_LEDS+15)/16);
}
