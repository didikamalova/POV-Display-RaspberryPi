/* Filename: RTTmeasure.h
 * This module computes the round trip time by reading hall sensor events. The ultimate aim
 * is to be able to return the column number the frame is currently at, so the values the LED
 * strip needs to driven to can be computed.
 */
#ifndef RTTMEASURE_H
#define RTTMEASURE_H

#include "hall.h"

// initializes RTT code
// initializes hall sensor and computes average time between each magnet
void RTT_init(void);

// Updates last event time by reading last hall event
// This is called during the intialization/computing average function
void get_event_time_init(void);

// Wrapper function to return last hall sensor event time
unsigned int last_hall_event_time(void);

// Stores the measured interval time between two magnets for all magnet
// segments for 3 rotations. Stores values in an array called measured_time_intervals.
void find_measured_intervals(void);

// Computes the amount of time to move between each colum in an image
// based on the round trip time measurements from the RTT_init average time
// in interval computations.
const unsigned int time_per_column(void);

// Finds and stores in an array called col_start_in_segment the starting column that
// is in line with each magnet.
void find_start_col_segment(void);

// Finds the amount of time the circular frame has spent in the current segment
unsigned int time_in_cur_segment(void);

// Returns the last event time of the last hall sensor event
// This ignores the ringbuffer implementation in the hall interrupts and only
// keeps track of the immediate last hall event to determine the relevant parameters for the current
// magnet segment.
void get_imm_event_time(void);

// Returns the column number the LEDs should currently be displaying 
unsigned int find_column(void);

// Returns the column number the LEDs on the opposite side of the circular frame should
// be displaying
unsigned int find_opposite_column(void);


#endif


