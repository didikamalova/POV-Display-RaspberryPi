#include "apa102.h"
#include "spi.h"
#include "uart.h"
#include "timer.h"
#include "hall.h"
#include "gpio.h"
#include "printf.h"


void main(void)
{
	gpio_init();
	uart_init();
	hall_init();
  	apa102_init();

	printf("Now initialize hall:\n");
//	hall_init();
	printf("Hall module initialized.\n");


	printf("\nNow driving LED blue on detection: \n");
//	
    apa102_clear(255, 255, 0, 0);
	printf("LED strip driven blue.\n");
    apa102_show();

    uart_putchar(EOT);

}
