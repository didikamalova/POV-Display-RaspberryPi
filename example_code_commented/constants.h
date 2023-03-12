#pragma once

#define LED_PIN_CLK 8
#define LED_PIN_DIN 9
#define LED_SERIAL_FREQ (19 * 1000 * 1000) // pixels have a 19 MHz refresh rate - fps refresh rate

// Global brightness value 0-31
// Limit to 50% as we don't have enough power
#define BRIGHTNESS 16
#define SHOW_DOT_MATRIX_STYLE 1

// they have 144 pixels/ metre
#define N_VERTICAL_RESOLUTION 55 // Can technically fit 55 LED strips across either side of outer rim.
#define N_HORIZONTAL_RESOLUTION 120 // based on thickness of circular frame and surface area of complete spherical shape.
#define N_CHANNELS_PER_PIXEL 3 // RGB channels for pixels

#define PIN_HALL_SENSOR 5
#define N_MAGNETS 8

#define SPI_DEV spi0
#define SPI_PIN_CS 17U
#define SPI_PIN_SCK 18U
#define SPI_PIN_MOSI 16U 
#define SPI_PIN_MISO 19U  
#define SPI_BAUD_RATE 1.953125*1000*1000
#define SPI_MASTER_END_BYTE 42
#define SPI_SLAVE_END_BYTE 255 
#define SPI_COM_START_BYTE 48
#define SPI_DATA_JUNK_SIZE 8192


// Computed parameters based on the previously set values
#define N_PIXEL (N_VERTICAL_RESOLUTION*N_HORIZONTAL_RESOLUTION) // number of pixels
#define N_BUFFER_SIZE_PER_COLUMN (N_VERTICAL_RESOLUTION*N_CHANNELS_PER_PIXEL) // size in bytes per column
#define N_BUFFER_SIZE (N_PIXEL*N_CHANNELS_PER_PIXEL) // total size in bytes

