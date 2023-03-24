#include "apa102.h"
#include "spi.h"
#include "uart.h"
#include "timer.h"
#include "hall.h"

// comment out tests we don't wish to run
void main(void)
{
    uart_init();
    //hall_init(); // commented out for post-demo day testing
    apa102_init();

	// simple LED driver test
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

	// simple LED driver initialization check
	apa102_clear(RED);
	apa102_show();
	timer_delay(3);

	// simple hall event -> color change test
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
