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
#define PHA     1
#define CLKDIV 50

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
        led_data[i].brightness = 31;
        led_data[i].red = r;
        led_data[i].green = g;
        led_data[i].blue = b;
    }
}

void led_show(void)
{
    unsigned char start_frame[4] = {0}; // 32 bits of 0's
    unsigned char end_frame[NUM_LEDS/16]= {0xFF};

    // 8 start bits for each led frame (setup & brightness bit)
    unsigned char temp = {0xFF};

    //int overall = (NUM_LEDS + 1) * 4 + NUM_LEDS/16;
    unsigned char rx[76];

    // printf("\nStart frame...\n");
    spi_txrx(start_frame, rx, 4);

    // printf("\nLED frames...\n");
    for (int i = 0; i < NUM_LEDS; i++) {

        // first 8 bits are 1
        spi_txrx(temp, rx, 1);

        // 8 bits per r, g, b
        spi_txrx(&led_data[i].blue, rx, 1);
        spi_txrx(&led_data[i].green, rx, 1);
        spi_txrx(&led_data[i].red, rx, 1);
    }

    //printf("\nEnd frame...\n");
    spi_txrx(end_frame, rx, 1);
}