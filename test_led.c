#include "apa102.h"
#include "spi.h"
#include "uart.h"
#include "timer.h"


void test_set_led(void) {
    apa102_set_led(0, BLUE);
    apa102_set_led(1, RED);
    apa102_show();
    timer_delay(2);

    // n < 0
    apa102_set_led(-1, BLUE);
    apa102_show();
    timer_delay(1);

    // n >= NUM_LEDS
    apa102_set_led(73, RED);
    apa102_show();
    timer_delay(1);
}

void main(void)
{
    uart_init();
    apa102_init();
    printf("LED strip initialized!\n");

    apa102_clear(GREEN);
    test_set_led();

    uart_putchar(EOT);
}
