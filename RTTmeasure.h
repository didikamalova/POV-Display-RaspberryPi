#ifndef RTTMEASURE_H
#define RTTMEASURE_H

#include "hall.h"

// header file for RTTmeasure


void RTT_init(void);

// last event time
void get_event_time_init(void);

unsigned int last_hall_event_time(void);

void find_measured_intervals(void);

const unsigned int time_per_column(void);

void find_start_col_segment(void);

unsigned int time_in_cur_segment(void);

// call this
// then read last_hall_event_time
// use this to calculate col
void get_imm_event_time(void);

// new event time function
unsigned int find_column(void);

// new event time function
unsigned int find_opposite_column(void);



#endif


