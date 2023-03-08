#include "uart.h"
#include "mymodule.h"

void main(void)
{
    uart_init();
    hello("CS107e");
    uart_putchar(EOT);
}
