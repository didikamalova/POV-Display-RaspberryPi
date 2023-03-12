#include "uart.h"
#include "mymodule.h"

void main(void)
{
    uart_init();
    hello("CS107e");
    //led_init();
    uart_putchar(EOT);
}