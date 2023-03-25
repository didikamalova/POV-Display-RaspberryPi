#include "apa102.h"
#include "spi.h"
#include "uart.h"
#include "timer.h"
#include "assert.h"


void test_apa102_color(void) 
{
    color_t color = apa102_color(0x01, 0x02, 0x03);
    assert(color == 0xFF030201);

    color = apa102_color(0x00, 0x00, 0x00);
    assert(color == 0xFF000000);

    color = apa102_color(0xFF, 0xFF, 0xFF);
    assert(color == 0xFFFFFFFF);
}


void test_apa102_clear(void) 
{
    apa102_clear(RED);
    apa102_show();
    timer_delay_ms(1000);

    apa102_clear(GREEN);
    apa102_show();
    timer_delay_ms(1000);

    apa102_clear(BLUE);
    apa102_show();
    timer_delay_ms(1000);
}

void test_apa102_set_led(void) 
{
    for (int i = 0; i < NUM_LEDS; i++) {
        apa102_set_led(i, RED);
        apa102_show();
        timer_delay_ms(300);
    }

    // going outside the buffer frame
    apa102_set_led(NUM_LEDS, RED);
    apa102_show();
    timer_delay_ms(1000);

    apa102_set_led(-1, RED);
    apa102_show();
    timer_delay_ms(1000);
}


void main(void)
{
    uart_init();
    apa102_init();
    printf("LED strip initialized!\n");

    apa102_clear(GREEN);
    apa102_show();
    test_apa102_color();
    test_apa102_clear();
    apa102_clear(GREEN);
    apa102_show();
    test_apa102_set_led();

    uart_putchar(EOT);
    printf("Finished all tests!\n");
}