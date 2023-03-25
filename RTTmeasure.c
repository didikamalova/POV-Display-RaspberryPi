/* Filename: RTTmeasure.c
 * This file contains the code for calculating the round trip time for the hall sensor
 * mounted on the spinning circular frame. The code starts reading the time as soon as 
 * RTT is initialized, so there must be a delay in the main function to account for 
 * the motor speeding up, prior to initialization.
 * 
 * The code calculates the average round trip time using the 6 magnets and then works out
 * the average time per column. The code then keeps track of the changing column numbers
 * and standardizes one column above the magnet to ensure consistency among the projected
 * images, which is why we used 6 magnets. The magnets were not equi-distant apart, so we had
 * to keep track of measured interval times. The column numbers are used to know what 'pixels'
 * each LED should be driven to in that position on the globe.
 *
 * Typically, frames per second is defined by the number of rotations of the motor per second (RPM/60).
 * This code computes columns 0 to HORIZONTAL_RESOLUTION for every frame while the motor is on, if find_column
 * called in an infinite while loop.
 *
 * Citation: Andreas Rottach, github username: rottaca
 * Link: https://github.com/rottaca/PovGlobe/blob/master/pico_src/Renderer/RTTMeasure.hpp
 * Our implementation of the RTT code was based on this approach. However, our code was written from scratch after
 * looking over this code and was designed to interface with the way we had implemented hall sensor interrupts. Our
 * magnets were also not equal distant apart, but his code assumes that they were, so our code was written to discard this
 * assumption. This involved keeping track of a lot more variables and data.
 */
#include "hall.h"
#include "timer.h"
#include "constants.h"
#include "printf.h"
#include "string.h"
#include "gpio.h"
#include "apa102.h"
#include "uart.h"

static volatile int prev_magnet = 0;
static volatile int cur_magnet = 0;
static unsigned int measured_intervals[NUM_MAGNETS*3];
static unsigned int avg_intervals[NUM_MAGNETS];
static unsigned int col_start_in_segment[NUM_MAGNETS];
volatile unsigned int event_time = 0;
volatile unsigned int prev_time = 0;
unsigned int RTT_time = 0;
volatile unsigned int column = 0;

void find_avg_intervals(void);
void find_start_col_segment(void);

// RTT init initializes hall sensor and then calculates average RTT and column time
// based on horizontal resolution (i.e. no. of columns).
void RTT_init(void) {
	hall_init(); // hall code now initialized
	timer_init();

	memset(measured_intervals, '\0', sizeof(measured_intervals));
	memset(avg_intervals, '\0', sizeof(avg_intervals));

	find_avg_intervals();
	find_start_col_segment(); // find the starting column above each magnet

}

// updates last hall event time
void get_event_time_init(void) {
    cur_magnet = hall_read_event(); // must continuously read this somewhere in code
    // commented out code is a time buffer for when the motor turns on to allow for 
    // the motor to speed up to a constant speed
//	if (event_time == 0) {
//	    unsigned int time_start = timer_get_ticks();
//		while (timer_get_ticks() - time_start >= 5*1000*1000) {
//	        cur_magnet = hall_read_event();
//	    }
//	}
    if (cur_magnet != prev_magnet) { // detects magnet change
		prev_magnet = cur_magnet;
		event_time = timer_get_ticks();
	}
}

// wrapper function for last hall event time
unsigned int last_hall_event_time(void) {
    return event_time;
}

// This function stores measured intervals between magnets for 3 rotations
// in an array called measured_intervals.
void find_measured_intervals(void) {
		    get_event_time_init();
			// essentially wait until next hall reading
		    while (last_hall_event_time() == prev_time) {
			    get_event_time_init();
			}
			prev_time = last_hall_event_time();
    // Store time between magnet segments for 3 full rotations
    for (int i = 0; i < NUM_MAGNETS*3; i++) {
		    get_event_time_init();
		    while (last_hall_event_time() == prev_time) {
			    get_event_time_init();
			}
			// calculate interval time between magnets
			measured_intervals[i] = last_hall_event_time() - prev_time;
			prev_time = last_hall_event_time();
	}
}


// once we have the measured intervals, we no longer care about the ringbuffer
// we just want which_magnet at any given moment
void find_avg_intervals(void) {
    find_measured_intervals();
    for (int i = 0; i < NUM_MAGNETS; i++) {
		avg_intervals[i] = (measured_intervals[i] + measured_intervals[NUM_MAGNETS] + 
								measured_intervals[NUM_MAGNETS*2])/3;
	}
    for (int i = 0; i < NUM_MAGNETS; i++) {
		RTT_time += avg_intervals[i];
	}
}

const unsigned int time_per_column(void) {
    return RTT_time / HORIZONTAL_RESOLUTION;
}

// find the start column in each segment
// this is so the column would remain consistent frame to frame
void find_start_col_segment(void) {
     col_start_in_segment[0] = 0;
     for (int i = 1; i < NUM_MAGNETS; i++) {
	      // Column start determined by time in segment divided by the time per column to get no. of columns
		  // in segment. This is the offset to be added to the previosuly calculated column start of the
		  // previous magnet.
          col_start_in_segment[i] = col_start_in_segment[i-1] + (avg_intervals[i-1] / time_per_column());
	 }
}

// time in segment we're currently in based on
// hall sensor reading.
unsigned int time_in_cur_segment(void) {
    return avg_intervals[cur_magnet - 1];
}

// This function updates event time for the last hall sensor reading, the current magnet
// and the start column we're at.
// This is to ignore the ring buffer implementation of the hall sensor interrupts.
// This is because we don't need to keep track of every interrupt, but only at the 
// very moment we decide to call this function to find the column. 
void get_imm_event_time(void) {
   cur_magnet = get_which_magnet(); // function in hall sensor code to return current magnet
   if (cur_magnet != prev_magnet) {
		event_time = timer_get_ticks();
		prev_magnet = cur_magnet;
		column = col_start_in_segment[cur_magnet - 1];
   }
}

// Find the current column we're at that we need to display
unsigned int find_column(void) {
    get_imm_event_time();
	if ((timer_get_ticks() - event_time) >= time_per_column()) {
        column = (column + 1) % HORIZONTAL_RESOLUTION; // increment column by one, once time per column passes
	}
	return column;
}

// Find opposite column to display on the LED strip on the opposite side of the circular frame
unsigned int find_opposite_column(void) {
	return (column + (HORIZONTAL_RESOLUTION/2)) % HORIZONTAL_RESOLUTION;
}

// Testing code
// Had more printf statements in code to debug too
//void main(void) {
  //  RTT_init();
//	unsigned int prev_column = -1;
//	//hall_init();
//	while (1) {
//	    //int magnet = hall_read_event();
//		//printf("%d", magnet);
//	    unsigned int fcolumn = find_column();
//		if (fcolumn != prev_column) {
//	        printf("%d\n", fcolumn);
//		    prev_column = fcolumn;
//			//uart_putchar('-');
//		}
//	}
//}
//

