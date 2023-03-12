#include "spi.h"

// SPI parameters
#define POL     0
#define PHA     0
#define CLKDIV  40

void led_init(void) {
    spi_init(POL, PHA, CLKDIV);
    printf("spi initialized!\n");
}