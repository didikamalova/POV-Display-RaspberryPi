#include "hall.h"
#include "timer.h"
#include "constants.h"
#include "printf.h"
#include "string.h"

// code to measure the speed
// frames per second is defined by no of rotations of motor per second (or RPM/60)

// track which_magnet variable

// NOTE WHAT PAT SAID ABOUT UNSIGNED INT TIME DIFFERENCE - when clock maxes out

// Naomi's hall sensor code always starts counting magnets from 0
// would be nice to have uniform start and end magnets though?? add offset later if so
// if we start reading hall sensor from back of frame, that's what it will consider 
// the beginning
// keep this is mind when projecting an image - how would we work this into code? i.e.
// how would we know what orientation the hall sensor is in without physically moving
// it. I think we won't? We must always think about orientation when running the code,
// if orientation ever matters i.e. when projecting a static image of a face.

static volatile int prev_magnet = 0;
static volatile int cur_magnet = 0;
static unsigned int measured_intervals[NUM_MAGNETS*3];
static unsigned int avg_intervals[NUM_MAGNETS];
static unsigned int measured_RTT[4];
static unsigned int col_start_in_segment[NUM_MAGNETS];
volatile unsigned int event_time;
volatile unsigned int prev_time = 0;
unsigned int RTT_time = 0;
volatile unsigned int column = 0;

void find_avg_intervals(void);
void find_start_col_segment(void);

// we need RTT init for initializing hall sensor and then calculating these averages
void RTT_init(void) {
    hall_init(); // hall code now initialized
	timer_init();
	memset(measured_intervals, '\0', sizeof(measured_intervals));
	memset(avg_intervals, '\0', sizeof(avg_intervals));
	memset(measured_RTT, '\0', sizeof(measured_RTT));

	find_avg_intervals();
	find_start_col_segment();

	//measured_intervals = malloc(NUM_MAGNETS*3);
	//avg_intervals = malloc(NUM_MAGNETS);
	//need to be constantly reading events though like in keyboard
}

//use timer_get_ticks()

// we should be running the hall code in this file
// change name from main to something else
// and then call it here

// or combine this file and that file
// add times to a list in that file and then use the info from that here?

// last event time
void get_event_time_init(void) {
    cur_magnet = hall_read_event(); // must continuously read this somewhere in code
    if (cur_magnet != prev_magnet) {
		prev_magnet = cur_magnet;
		event_time = timer_get_ticks();
	}
}

unsigned int last_hall_event_time(void) {
    return event_time;
}

void find_measured_intervals(void) {
		    get_event_time_init();
		    while (last_hall_event_time() == prev_time) {
			    get_event_time_init();
			}
			prev_time = last_hall_event_time();
    for (int i = 0; i < NUM_MAGNETS*3; i++) {
		    get_event_time_init();
		    while (last_hall_event_time() == prev_time) {
			    get_event_time_init();
			}
            //printf("event time: %d\n", event_time/1000000);
			measured_intervals[i] = last_hall_event_time() - prev_time;
			prev_time = last_hall_event_time();
			if (i == NUM_MAGNETS || i == NUM_MAGNETS*2) {
			    measured_RTT[i / NUM_MAGNETS] = prev_time;
			}
	}
	get_event_time_init();
    while (last_hall_event_time() == prev_time) {
		get_event_time_init();
    }
    measured_RTT[3] = last_hall_event_time();
}


// once we have the measured intervals, we no longer care about the ringbuffer
// we just want which_magnet at any given moment
void find_avg_intervals(void) {
    find_measured_intervals();
    for (int i = 0; i < NUM_MAGNETS; i++) {
		avg_intervals[i] = (measured_intervals[i] + measured_intervals[NUM_MAGNETS] + 
								measured_intervals[NUM_MAGNETS*2])/3;
	}
    for (int i = 0; i < 2; i++) {
		RTT_time += measured_RTT[i+1] - measured_RTT[i];
	}
	RTT_time /= 3;
}

const unsigned int time_per_column(void) {
    //printf("RTT time: %d\n", RTT_time); // CONSIDER CHANGING THE WAY RTT TIME IS CALCUALTED BY USING AVG TIME INSTEAD OF AVERAGING TIMES ON YOUR OWN
    return RTT_time / HORIZONTAL_RESOLUTION;
}


void find_start_col_segment(void) {
     col_start_in_segment[0] = 0;
     printf("column start: %d ", col_start_in_segment[0]);
	 printf("average interval: %d\n", avg_intervals[0] / 1000);
     for (int i = 1; i < NUM_MAGNETS; i++) {
	      printf("time per col: %d\n", time_per_column() / 1000);
          col_start_in_segment[i] = col_start_in_segment[i-1] + (avg_intervals[i-1] / time_per_column());
		  printf("column start: %d ", col_start_in_segment[i]);
		  printf("average interval: %d\n", avg_intervals[i] / 1000);
	 }
}

unsigned int time_in_cur_segment(void) {
    return avg_intervals[cur_magnet - 1];
}

// call this
// then read last_hall_event_time
// use this to calculate col
void get_imm_event_time(void) {
   printf("timer before: %d\n", timer_get_ticks());
   cur_magnet = get_which_magnet();
   printf("timer after: %d\n", timer_get_ticks());
   //printf("cur magnet: %d prev_magent: %d\n", cur_magnet, prev_magnet);
   if (cur_magnet != prev_magnet) {
		event_time = timer_get_ticks();
		prev_magnet = cur_magnet;
		column = col_start_in_segment[cur_magnet - 1];
		printf("new magnet\n");
   }
   //printf("event time: %d\n", event_time/1000000);
}

// new event time function
unsigned int find_column(void) {
    get_imm_event_time();
    printf("timer: %d event_time: %d difference: %d time_per_column: %d\n", timer_get_ticks(), event_time, timer_get_ticks() - event_time, time_per_column());
	if ((timer_get_ticks() - event_time) >= time_per_column()) { // NOT GOING INTO THIS CONTINUOUSLY??
	    printf("changing column\n");
        column = (column + 1) % HORIZONTAL_RESOLUTION;
	}
	return column;
	//printf("%d\n", column);
}

// let's assume every magnet is same fixed distance apart

// find intervals function
    // add difference to list
	// do this for NUM_MAGNETS times
	// do this three times and then find average
// add average to new global list

// calculate average


// get column
// call hall sensor code - while (1), hall read
// using averages
// every average is no. of seconds magnets is apart
// find columns per segment  by doing horizontal res/num of magnets
// find time per column by doing columns per segment / avg time
// find cur column by incrementing column every time start - cur >= avg
// once this happens start = cur and column++
// column = column % horizontal res

// location to write in in buffer would be column x buffer size per column


// get opposite column
// this is just (column + horizontal res/2) % horizontal res


// we should have at least NUM_MAGNETS*3 event times


// workflow to use this module:
// RTT_init()
// need to end up constantly reading columns not to miss one as the globe spins

void main(void) {
    RTT_init();
	unsigned int prev_column = -1;
	//hall_init();
	while (1) {
	    //int magnet = hall_read_event();
		//printf("%d", magnet);
	    unsigned int fcolumn = find_column();
		if (fcolumn != prev_column) {
	        printf("%d\n", fcolumn);
		    prev_column = fcolumn;
			//uart_putchar('-');
		}
	}
}
//
