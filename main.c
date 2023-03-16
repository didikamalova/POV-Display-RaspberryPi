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
	printf("Checkpoint\n");
//	RTT_init();
	hall_init();
	printf("Made it\n");
//	hall_init();
  	apa102_init();

	printf("Now initialize hall:\n");
//	hall_init();
//	RTT_init();
	printf("Hall module initialized.\n");


	printf("\nNow driving LED blue on detection: \n");
//	
	int something = hall_read_event();
    apa102_clear(255, 255, 0, 0);
	printf("LED strip driven blue.\n");
    apa102_show();

	int another = hall_read_event();
	apa102_clear(0,255,0,0);
	printf("LED strip off.\n");
	apa102_show();

	int ungabunga = hall_read_event();
	apa102_clear(255, 0, 255, 0);
	printf("GREEN.\n");
	apa102_show();

	int ungabunga2 = hall_read_event();
	apa102_clear(255, 0, 0, 255);
	apa102_show();

    uart_putchar(EOT);

}