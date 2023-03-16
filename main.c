#include "apa102.h"
#include "spi.h"
#include "uart.h"
#include "timer.h"


void main(void)
{
    uart_init();
    apa102_init();

    apa102_clear(255, 255, 0, 0);
    apa102_show();

    uart_putchar(EOT);
}
