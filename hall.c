/*
 * Hall driver code base on Pat's implementation provided in the 107E library.
 */

#include "constants.h"
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

// change I/O pins as needed
static const unsigned hall_pin = GPIO_PIN2;

// Global variables for magnet event tracking
static unsigned int totalmagnets = NUM_MAGNETS;
static unsigned int magnetnum = 0; // which magnet we have passed
static unsigned int magnetevent = 0; // high (1) or low (0)
static unsigned int lastmagnetevent = 0;
volatile int which_magnet;

rb_t *rb;

void hall_init(void) {
	rb = rb_new();
	which_magnet = 0;

	//printf("initialize interrupts completed\n");
	gpio_set_input(hall_pin);
  	gpio_set_function(hall_pin, GPIO_FUNC_INPUT);
  	gpio_set_pullup(hall_pin);
	gpio_enable_event_detection(hall_pin, GPIO_DETECT_HIGH_LEVEL);

    interrupts_init();
	gpio_interrupts_init();
	gpio_interrupts_register_handler(hall_pin, handle_hall, rb);
	gpio_interrupts_enable();
	interrupts_global_enable();
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

// Read a hall event w/ debouncing implemented
int hall_read_event(void) {
	while(rb_empty(rb)) {/* spin */};
	rb_dequeue(rb, &which_magnet);

	// DEBUG STATEMENTS
	//printf("%d\n", which_magnet);
	//uart_putchar('+');
	
	lastmagnetevent = 0;
	return which_magnet;
}
