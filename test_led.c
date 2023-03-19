#include "apa102.h"
#include "spi.h"
#include "uart.h"
#include "timer.h"


void test_set_led(void) {
    // set the first LED to blue
    apa102_set_led(0, BLUE);
    printf("First LED changed to 1!\n");
    apa102_show();
    timer_delay(1);
    
    // n < 0
    apa102_set_led(-1, BLUE);
    printf("Nothing changed!\n");
    apa102_show();
    timer_delay(1);

    // n >= NUM_LEDS
    apa102_set_led(73, RED);
    printf("Nothing changed!\n");
    apa102_show();
    timer_delay(1);
    
}

void main(void)
{
    uart_init();
    apa102_init();

    printf("LED strip initialized!\n");

    // set every LED to green
    apa102_clear(GREEN);
    apa102_show();

    //test_set_led();

    uart_putchar(EOT);
}
