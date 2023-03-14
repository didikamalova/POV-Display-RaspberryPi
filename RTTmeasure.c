#include "hall.c"
#include "timer.h"
#include "constants.h"

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

int prev_magnet = 0;

// timer_init()
//use timer_get_ticks()

// we should be running the hall code in this file
// change name from main to something else
// and then call it here

// or combine this file and that file
// add times to a list in that file and then use the info from that here?

// last event time
unsigned int get_event_time() {
    if (get_which_magnet() != prev_magnet) {
		
	} 
}


// new event time function


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


