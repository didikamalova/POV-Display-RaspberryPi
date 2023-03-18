#include "apa102.h"
#include "spi.h"
#include "uart.h"
#include "timer.h"
#include "hall.h"
#include "gpio.h"
#include "printf.h"
#include "RTTmeasure.h"
#include "interrupts.h"

void main(void)
{
	gpio_init();
	uart_init();
	hall_init();
  	apa102_init();

//	int something = hall_read_event();
//    apa102_clear(255, 255, 0, 0);
//	printf("LED strip driven blue.\n");
  //  apa102_show();

//	int another = hall_read_event();
//	apa102_clear(0,255,0,0);
//	printf("LED strip off.\n");
//	apa102_show();

//	int ungabunga = hall_read_event();
//	apa102_clear(255, 0, 255, 0);
//	printf("GREEN.\n");
//	apa102_show();

//	int ungabunga2 = hall_read_event();
//	apa102_clear(255, 0, 0, 255);
//	apa102_show();

	int count = 0;
	while(1) {
		hall_read_event();
		if (count == 0 || count == 3) {
			apa102_clear(255,255,0,0);
			count++;
		} else if (count == 1 || count == 4) {
			apa102_clear(255, 0, 0, 255);
			count++;
		} else {
			apa102_clear(255, 0, 255, 0);
			if (count == 2) {
				count++;
			} else {
				count = 0;
			}
		}
		apa102_show();
	}
    uart_putchar(EOT);

}
