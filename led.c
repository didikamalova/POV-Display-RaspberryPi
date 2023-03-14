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

#define CLKDIV 40

typedef struct BRGB {
    unsigned char brightness;
    unsigned char blue;
    unsigned char green;
    unsigned char red;   
} BRGB;

struct BRGB led_data[NUM_LEDS];

void led_init(void)
{
    spi_init(SPI_CE0, CLKDIV); 
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
    unsigned char start_frame[32] = {0};
    unsigned char end_frame[NUM_LEDS/2] = {1};
    unsigned char temp[3] = {1};

    unsigned char rx[2372];

    // printf("\nStart frame:\n");
    spi_transfer(start_frame, rx, 32);

    // printf("\nLED frames:\n");
    for (int i = 0; i < NUM_LEDS; i++) {
        spi_transfer(temp, rx, 3);

        // 5 bits for brightness
        spi_transfer(&led_data[i].brightness, rx, 5);

        // 8 bits per r, g, b
        spi_transfer(&led_data[i].blue, rx, 8);
        spi_transfer(&led_data[i].green, rx, 8);
        spi_transfer(&led_data[i].red, rx, 8);
    }

    // printf("\nEnd frame:\n");
    spi_transfer(end_frame, rx, NUM_LEDS/2);
}
