#include "spi.h"
#include "uart.h"

// SPI parameters
#define POL     0
#define CLKDIV  40

void led_init(void) {
    spi_init(POL, CLKDIV);
    printf("spi initialized!\n");
}