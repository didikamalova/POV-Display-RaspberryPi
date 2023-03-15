#include "led.h"
#include "mymodule.h"
#include "spi.h"
#include "uart.h"
#include "timer.h"


void main(void)
{
    uart_init();

    led_init();
    printf("LED strip initialized!\n");

    clear_strip(0, 0, 255);
    printf("LED strip cleared to blue!\n");
    led_show();
    timer_delay(2);

    clear_strip(0, 255, 0);
    printf("LED strip cleared green!\n");
    led_show();
    timer_delay(2);

    clear_strip(0, 0, 255);
    printf("LED strip cleared to blue!\n");
    led_show();
    timer_delay(2);

    uart_putchar(EOT);
}
