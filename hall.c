#include "constants.h"
/*
 * hall effect sensor 3144.
 *
 * http://www.allegromicro.com/~/media/Files/Datasheets/A3141-2-3-4-Datasheet.ashx?la=en
 *
 *
 * looking down from the top of the pyramid = power, ground, output (vout).
 * 	- vout to gpio2.
 *	- enable pullup so don't need a resistor.
 *
 * http://www.raspberrypi-spy.co.uk/2015/09/how-to-use-a-hall-effect-sensor-with-the-raspberry-pi/
 *
 * The output of these devices (pin 3) switches low when the magnetic
 * field at the Hall element exceeds the operate point threshold (BOP). At
 * this point, the output voltage is VOUT(SAT). When the magnetic field
 * is reduced to below the release point threshold (BRP), the device
 * output goes high. The difference in the magnetic operate and release
 * points is called the hysteresis (Bhys) of the device. This built-in
 * hysteresis allows clean switching of the output even in the presence
 * of external mechanical vibration and electrical noise.
 */

#include "gpio.h"
#include "gpio_extra.h"
#include "gpio_interrupts.h"
#include "uart.h"
#include "printf.h"
#include "interrupts.h"
#include "timer.h"
#include "ringbuffer.h"
#include "hall.h"

void handle_hall(unsigned int pc, void *aux_data);

// chang I/O pins as needed
static const unsigned hall_pin = GPIO_PIN2;
static const unsigned LED_pin = GPIO_PIN3;

// Global variables for magnet event tracking
static unsigned int totalmagnets = NUM_MAGNETS;
static unsigned int magnetnum = 0; // which magnet we have passed
static unsigned int magnetevent = 0; // high (1) or low (0)
static unsigned int lastmagnetevent = 0;
volatile int which_magnet;

rb_t *rb;
// Given function from Pat's hall.c code
//void print_magnet(unsigned int vout)
//{
//    printf(vout ?  "magnet out of range\n" : "magnet detected\n" );
//}

//int get_which_magnet(void);

void hall_init(void) {
	//rb_t *rb = rb_new();
	rb = rb_new();

//    gpio_init();
//    uart_init();
	printf("initialize interrupts completed\n");
	gpio_set_input(hall_pin);
  	gpio_set_function(hall_pin, GPIO_FUNC_INPUT);
  	gpio_set_pullup(hall_pin);
	gpio_enable_event_detection(hall_pin, GPIO_DETECT_HIGH_LEVEL);

	interrupts_init();
	gpio_interrupts_init();
	gpio_interrupts_register_handler(hall_pin, handle_hall, rb);
	gpio_interrupts_enable();
	interrupts_global_enable();
	which_magnet = 0;

}

void handle_hall(unsigned int pc, void *aux_data) {
	rb_t *rb = (rb_t *) aux_data;
	if (gpio_check_and_clear_event(hall_pin)) {
		magnetevent = 1;
		if (lastmagnetevent == 0) {
			magnetnum++;
			lastmagnetevent = 1;
	
			// change comparison val depending on how many magnets we use
			if (magnetnum > totalmagnets) magnetnum = 1;

			rb_enqueue(rb, magnetnum);
			which_magnet = magnetnum;
		}

	}
}

volatile int get_which_magnet(void) {
    //printf("get which magnet after avg: %d\n", which_magnet);
	lastmagnetevent = 0;
    return which_magnet;
}

int hall_read_event(void) {
//	while (1) {
		while(rb_empty(rb)) {/* spin */};
		rb_dequeue(rb, &which_magnet);
//		printf("%d\n", which_magnet);
		uart_putchar('+');
		lastmagnetevent = 0;
        //printf("get which magnet: %d\n", which_magnet);
		return which_magnet;
//	}

	// PAT'S ORIGINAL CODE
    // vout is 1 when the magnet is out of range of the sensor
//    print_magnet(1);
//	while(1) {
//  	while(gpio_read(hall_pin) == 1) {} // wait for low
//		print_magnet(0);
// 		while(gpio_read(hall_pin) == 0) {} // wait for high
//		print_magnet(1);		
//		}
}


//void main(void) {
//    hall_init();
//	while (1) {
//	     printf("%d\n", hall_read_event());
//	}
//}

