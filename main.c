#include "apa102.h"
#include "spi.h"
#include "uart.h"
#include "timer.h"
#include "hall.h"

void main(void)
{
    uart_init();
    hall_init();
    apa102_init();

//    for (int i = 0; i < 20; i++) {
//        apa102_clear(BLUE);
//       apa102_show();
//        timer_delay_ms(300);
//       apa102_clear(RED);
//        apa102_show();
//        timer_delay_ms(300);
//        apa102_clear(GREEN);
//        apa102_show();
//        timer_delay_ms(300);
//    }
	
	int count = 0;
	while(1) {
		hall_read_event();
		if (count == 0) {
			apa102_clear(BLUE);
			count++;
		} //else if (count == 1) {
			//apa102_clear(BLUE);
		//	count++;
		//} 
		else {
			apa102_clear(GREEN);
			count = 0;
		}
		apa102_show();
	}
    uart_putchar(EOT);
}
