#include "apa102.h"
#include "spi.h"
#include "uart.h"
#include "timer.h"
#include "hall.h"

void main(void)
{
    uart_init();
    //hall_init();
    apa102_init();

    for (int i = 0; i < 20; i++) {
        apa102_clear(BLUE);
        apa102_show();
        timer_delay_ms(300);
        apa102_clear(RED);
        apa102_show();
        timer_delay_ms(300);
        apa102_clear(GREEN);
        apa102_show();
        timer_delay_ms(300);
    }
	
	// commented out code for hall-sensor driving testing

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

	apa102_clear(RED);
	apa102_show();

//	int count = 0;
//	while(1) {
//		hall_read_event();
//		if (count == 0) {
//			apa102_clear(RED);
//			count++;
//		} else if (count == 1) {
//			apa102_clear(BLUE);
//			count++;
//		} else {
//			apa102_clear(GREEN);
//			count = 0;
//		}
//		apa102_show();
//	}
    uart_putchar(EOT);
}