#ifndef HALL_H
#define HALL_H

// header file for hall sensor

void hall_init(void);
int hall_read_event(void);
volatile int get_which_magnet(void);

#endif
