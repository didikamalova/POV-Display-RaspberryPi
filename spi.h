#ifndef SPI_H
#define SPI_H

void spi_init(unsigned pol, unsigned pha, unsigned clk_div);
void spi_txrx(unsigned char* txbuf, unsigned char* rxbuf, unsigned len);

<<<<<<< HEAD
#endif
=======
#define SPI_CE0 0
#define SPI_CE1 1

void spi_init(unsigned chip_select, unsigned clock_divider);
void spi_transfer(unsigned char *tx, unsigned char *rx, unsigned len);

#endif /* SPI_H */
>>>>>>> 97f40e92a04ec85177348cd2454db0769749843d
