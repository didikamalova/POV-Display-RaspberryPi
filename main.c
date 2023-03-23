#include "apa102.h"
#include "spi.h"
#include "uart.h"
#include "timer.h"

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

    uart_putchar(EOT);
}