#ifndef HALL_H
#define HALL_H

#include "constants.h"

// header file for hall sensor

void hall_init(void);
void handle_hall(unsigned int pc, void *aux_data);
int hall_read_event(void);
volatile int get_which_magnet(void);

#endif
