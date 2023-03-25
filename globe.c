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

// doing graphics for globe
// consider converting an image to a bitmap and using that

//typedef unsigned int color_t;

// idea is to have a render buffer and a input buffer
// render buffer is the drawing buffer
// input buffer is the shown buffe

void main(void) {
// earth_jpg
    // rbga - in globe array
  // abgr
  // 60 across, 120 down
  
  uart_init();
  apa102_init();

//  apa102_clear(0xff0000ff);
//  apa102_show();
//  timer_delay(10);

//  RTT_init();

  unsigned int column = 0;

  apa102_clear(0xff0000ff);
  apa102_show();
  timer_delay(3);

   // iterate through vertical resolution which is 60*4
   // 120 across
   // 60 down
   while(1) {
		for (int i = VERTICAL_RESOLUTION - 1; i >= 0; i--) {
		    color_t c = soccer[column + (i*HORIZONTAL_RESOLUTION)];
		    apa102_set_led(i, c);
	    }
		for (int i = 0; i <= VERTICAL_RESOLUTION - 1; i++) {
		    unsigned int opp_column = (column + HORIZONTAL_RESOLUTION/2) % HORIZONTAL_RESOLUTION;
			color_t c = soccer[opp_column + (i*HORIZONTAL_RESOLUTION)];
		    apa102_set_led(i + VERTICAL_RESOLUTION - 1, c);
	    }
		apa102_show();

		timer_delay_us(20);

    }

//  unsigned int prev_column = -1;
//  while (1) {
//    unsigned int column = find_column();
//    unsigned int opp_column = find_opposite_column();
//    if (column != prev_column) {
//       prev_column = column;
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
