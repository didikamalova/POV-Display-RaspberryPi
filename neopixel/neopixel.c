/*
 * Julie Zelenski, Winter 2019
 * Sample program to drive strip of Neopixels (WS2811/2812 LEDs)
 */

// Editing this code to mess around with graphics arrays on the neopixel strip

#include "gl.h"
#include "gpio.h"
#include "timer.h"
#include "printf.h"

#define NEO_DATA_GPIO GPIO_PIN20

// this function written in assembly for precise timing, see neo_timing.s
void send_bit(unsigned int pin, unsigned int bit);

static void send_byte(unsigned char byte) 
{
    // neopixel bits sent in order most-to-least significant
    for (unsigned char mask = 1 << 7; mask != 0 ; mask >>= 1 ) { 
        send_bit(NEO_DATA_GPIO, byte & mask);
    }     
    // inter-bit gap not v sensitive, but must not exceed latch delay (see below)    
}

static void send_pixel_color(color_t c)  
{  
    // color_t stores (least)BGRA(most), neopixel bytes sent in order G-R-B
    send_byte(c >> 8);  // G 
    send_byte(c >> 16); // R
    send_byte(c);       // B
    // inter-byte gap not v sensitive, but must not exceed latch delay (see below)    
}

// after send sequence of pixels, must hold data low for pixels to latch and display        
// wait must be at least 55us (shorter might not work, but longer totally fine)
// No need to do this in assembly as 55us is A Long Time, relatively speaking
// Means neopixel frame rate tops out around max of ~20K frames/sec 
// (which is way, way faster than human eye, our vision is 10-50 Hz)
// Must take care when sending sequence to not exceed minium latch delay 
// in between sending successive bits/bytes
static void latch_frame(int frames_per_sec)
{
    #define US_MIN_LATCH 55    // Minimum width to pause after frame complete
    int usec_to_wait = 1000000/frames_per_sec; // Desired pause betewen frames
    if (usec_to_wait < US_MIN_LATCH) usec_to_wait = US_MIN_LATCH;
    timer_delay_us(usec_to_wait);  
}

static inline color_t intensity(color_t c, int percentage)
{
    float scale = percentage/100.0;
    unsigned char blue = (c & 0xff) * scale;
    unsigned char green = ((c >> 8) & 0xff) * scale;
    unsigned char red = ((c >> 16) & 0xff) * scale;
    return gl_color(red, green, blue);
}

void send_sequence(color_t colors[], int n, int brightness)
{
    // above intensity calculation takes ~10 us so can be squeezed in between pixels
    // without triggering latch, but if have more extensive work to do, could instead
    // first prep entire sequence, then send in one continuous go
    for (int i = 0; i < n; i++) {
        color_t c = intensity(colors[i], brightness % 50);
        send_pixel_color(c);
    }
    latch_frame(25);
}

void rainbow(void)
{
    color_t colors[] = {GL_BLACK, GL_RED, GL_ORANGE, GL_YELLOW, GL_GREEN, GL_BLUE, GL_INDIGO, GL_PURPLE};
    int n = sizeof(colors)/sizeof(*colors);

    int brightness = 0;
    while (1)  {
        while (++brightness < 50)  // fade in
            send_sequence(colors, n, brightness);
        while (--brightness > 0)   // fade out
            send_sequence(colors, n, brightness);
    }
}

void cycle(color_t color, int nleds)
{
    int on_index = 0;

    while (1) {
        for (int i = 0; i < nleds; i++) {
            color_t c = (i == on_index ? color : GL_BLACK);
            send_pixel_color(c);
        }
        latch_frame(50);
        on_index = (on_index + 1) % nleds;
    }
}

// general test function to generate a display buffer and iterate through each col
void generate_display_array(int rows, int leds, color_t color1, color_t color2) {
	color_t display[rows][leds]; 
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < leds; j++) {
			if (i % 2 == 0) {
				display[i][j] = color1;
			} else {
				display[i][j] = color2;
			}
		}
	}

	// DEBUGGING PRINTF STATEMENTS
//	printf("color: %d\n", display[0][0]);
//	printf("color name: %d\n",GL_GREEN);
//	printf("color name: %d\n",GL_BLUE);
//	for (int i = 0; i < leds; i++) {
//		printf("color: %d\n", display[0][i]);
//	}
	
	// some observations: must be alternating between states for display to work
	int n;
	while(1) {
		n = sizeof(display[0])/sizeof(*display[0]);
		send_sequence(display[0],n,0);
		timer_delay(1);
		send_sequence(display[1],n,0);
//		for (int i = 0; i < rows; i++) {
//			send_sequence(display[i],leds,0);
//			timer_delay(1);
//		}
	}
	
}


void main(void) 
{
    gpio_init();
    timer_init();
    gpio_set_output(NEO_DATA_GPIO);

//    rainbow();
//    number of neopixels on our current np LED strip: 72
//    cycle(GL_PURPLE, 72);
	generate_display_array(5, 70, GL_GREEN, GL_BLUE);
}
