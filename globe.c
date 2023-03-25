/* Filename: globe.c
 * This file contains the graphics code for a POV globe. It iterates through a HORIZONTAL_RESOLUTION by
 * VERTICAL_RESOLUTION image array stored in separate header files as they are quite long. The current implementation
 * works with a soccer ball and iterates through each column at an arbitrary 20 microsecond speed, independent of the 
 * hall sensor readings. The intended implementation is commented out below and uses the RTT_measure round trip time
 * measurement code to find the column number that the strip should be displaying and driving the LEDs in that way. The
 * RTT code works in a 10 second delay to allow the motor to reach an adequate speed before beginning to measure the 
 * average round trip time.
 */
# include "apa102.h"
# include "RTTmeasure.h"
# include "timer.h"
# include "uart.h"
# include "gpio.h"
# include "constants.h"
# include "printf.h"
# include "spi.h"
# include "checkerboard.h"
# include "soccer.h"
# include "earth.h"

void main(void) {
  
  uart_init();
  apa102_init();

//  apa102_clear(0xff0000ff); // indicates code is running
//  apa102_show();
//  timer_delay(10); // time delay to allow motor to speed up as soon as pi and motor turned on

//  RTT_init();

  unsigned int column = 0;

  apa102_clear(0xff0000ff); // indicates code is running
  apa102_show();
  timer_delay(3);

   // Iterate through image array at correct column forever
   // Image array is HORIZONTAL_RESOLUTION = 120 across
   // and VERTICAL_RESOLUTION = 60 down
   while(1) {
		for (int i = VERTICAL_RESOLUTION - 1; i >= 0; i--) {
		    color_t c = soccer[column + (i*HORIZONTAL_RESOLUTION)]; // start reading from bottom to top as LEDs driven from bottom
		    apa102_set_led(i, c); // sets individual LED in the render buffer
	    }
		for (int i = 0; i <= VERTICAL_RESOLUTION - 1; i++) {
		    // start reading from top to bottom as LEDs driven from top to bottom
		    unsigned int opp_column = (column + HORIZONTAL_RESOLUTION/2) % HORIZONTAL_RESOLUTION;
			color_t c = soccer[opp_column + (i*HORIZONTAL_RESOLUTION)];
		    apa102_set_led(i + VERTICAL_RESOLUTION - 1, c); // starts from LED 59 for opposite column
	    }
		apa102_show(); // drives LEDs

		timer_delay_us(20); // arbitrary time delay

    }

//  unsigned int prev_column = -1;
//  while (1) {
//    unsigned int column = find_column(); // column to currently drive LEDs to
//    unsigned int opp_column = find_opposite_column(); // opposite column to drive LEDs to
//    if (column != prev_column) { // only drive if column has changed
//      prev_column = column;
//		for (int i = VERTICAL_RESOLUTION - 1; i >= 0; i--) {
//		    color_t c = soccer[column + (i*HORIZONTAL_RESOLUTION)];
//		    apa102_set_led(i, c);
//	    }
//		for (int i = 0; i <= VERTICAL_RESOLUTION - 1; i++) {
//			color_t c = soccer[opp_column + (i*HORIZONTAL_RESOLUTION)];
//		    apa102_set_led(i + VERTICAL_RESOLUTION - 1, c);
//	    }
//      apa102_show();
//      }
//  }
}
