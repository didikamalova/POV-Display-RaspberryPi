#include "RTTmeasure.h"
#include "printf.h"
#include "uart.h"


void main(void) {
    RTT_init();
	unsigned int prev_column = -1;
	//hall_init();
	while (1) {
	    //int magnet = hall_read_event();
		//printf("%d", magnet);
	    unsigned int column = find_column();
		if (column != prev_column) {
	        printf("%d\n", column);
		    prev_column = column;
			//uart_putchar('-');
		}
	}
}
