#include "led.h"
#include "mymodule.h"
#include "spi.h"
#include "uart.h"



void main(void)
{
    uart_init();
    led_init();
    printf("LED strip initialized!\n");

    clear_strip(0, 0, 0);
    led_show();
    
    uart_putchar(EOT);
}