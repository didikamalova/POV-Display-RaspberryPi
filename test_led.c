#include "apa102.h"
#include "spi.h"
#include "uart.h"
#include "timer.h"


void main(void)
{
    uart_init();

    apa102_init();
    printf("LED strip initialized!\n");

    apa102_clear(255, 255, 0, 0);
    printf("LED strip cleared to blue!\n");
    apa102_show();
    timer_delay(2);

    uart_putchar(EOT);
}
