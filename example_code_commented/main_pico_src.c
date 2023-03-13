/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <math.h>
#include <cstring>

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/time.h"

#include "hardware/gpio.h"

#include "LEDController.hpp"
#include "SpiDataReader.hpp"



/// TODO This needs cleanup!
bool showNextInitFrame(uint32_t frameNumber, uint8_t * pixels){
    //printf("Init frame %d\n", frameNumber);
    
    const float_t pi = 3.14159f;  
    
    if (frameNumber == 0){
      // Show calibration stribes (RGB 4 times 90degrees angle)
      uint32_t pixel_idx = 0;
	  // iterate through frame
      for (size_t j = 0; j < N_HORIZONTAL_RESOLUTION; j++)
      {
        for (size_t i = 0; i < N_VERTICAL_RESOLUTION; i++)
        {
		    // only adds three stripes at 90 degree angles
            pixels[pixel_idx] = (j % (N_HORIZONTAL_RESOLUTION/4) == 0) ? 128 : 0;
			pixels[pixel_idx+1] = (j % (N_HORIZONTAL_RESOLUTION/4) == 1) ? 128 : 0;
            pixels[pixel_idx+2] = (j % (N_HORIZONTAL_RESOLUTION/4) == 2) ? 128 : 0;
            
            pixel_idx+=N_CHANNELS_PER_PIXEL; // skips pixel index by number of channels (4 bytes per channel)
        }
      }
	  // this depends on fps - how fast it spins?
    } else if (frameNumber < 120){
      // Keep it visible for a fixed number of cycles
      // Do nothing
    } else if (frameNumber < 120+N_VERTICAL_RESOLUTION){
      // Show red/green colors fading in from top to bottom
      const uint32_t seq_offset = frameNumber - 120; // this allows it to fade in for 120 cycles?
      uint32_t pixel_idx = 0;
      for (size_t j = 0; j < N_HORIZONTAL_RESOLUTION; j++)
      {
        for (size_t i = 0; i < N_VERTICAL_RESOLUTION; i++)
        {
            pixels[pixel_idx] = (i < seq_offset) ? 128 : 0;
            pixels[pixel_idx+1] = (i < seq_offset) ? i * 128 / N_VERTICAL_RESOLUTION : 0;
            pixels[pixel_idx+2] = 0;
            
            pixel_idx+=N_CHANNELS_PER_PIXEL;
        }
      }
    } else if (frameNumber < 120+2*N_VERTICAL_RESOLUTION){
      // Show cos/sin pattern with motion along the vertical axis
	  // seq offset defines how many pixels you want to write to at once 
	  // allows for fade pattern
      const uint32_t seq_offset = frameNumber - 120 - N_VERTICAL_RESOLUTION; // FRAME NUMBER
      uint32_t pixel_idx = 0;
      for (size_t j = 0; j < N_HORIZONTAL_RESOLUTION; j++)
      {            
        //const float_t horizontal_arc_ratio = 2*pi*(float_t)((j + seq_offset)%N_HORIZONTAL_RESOLUTION) / (N_HORIZONTAL_RESOLUTION-1);  
        for (size_t i = 0; i < N_VERTICAL_RESOLUTION; i++)
        {
            if(i < seq_offset){
              const float_t vertical_arc_ratio = pi*(float_t)((i + 3*seq_offset)%N_VERTICAL_RESOLUTION) / (N_VERTICAL_RESOLUTION-1);
		      // change color by a little bit across vertical
              pixels[pixel_idx] = 64 + 64*sin(3*vertical_arc_ratio);
              pixels[pixel_idx+1] = 64 + 64*sin(2*vertical_arc_ratio);
              pixels[pixel_idx+2] = 64 + 64*cos(2*vertical_arc_ratio);
            }
            
            pixel_idx+=N_CHANNELS_PER_PIXEL;
        }
      }
    } else if (frameNumber < 120+3*N_VERTICAL_RESOLUTION){
      // Delete last pattern by fading out from top to bottom
      const uint32_t seq_offset = frameNumber - 120 - 2*N_VERTICAL_RESOLUTION;
      uint32_t pixel_idx = 0;
      for (size_t j = 0; j < N_HORIZONTAL_RESOLUTION; j++)
      {            
        for (size_t i = 0; i < N_VERTICAL_RESOLUTION; i++)
        {
            if(i <= seq_offset){
              pixels[pixel_idx] = 0;
              pixels[pixel_idx+1] = 0;
              pixels[pixel_idx+2] = 0;
            }
            
            pixel_idx+=N_CHANNELS_PER_PIXEL;
        }
      }
    } else if (frameNumber < 120+4*N_VERTICAL_RESOLUTION){
      // Show horizontal rgb stripes 
      const uint32_t seq_offset = frameNumber - 120 - 3*N_VERTICAL_RESOLUTION;
      uint32_t pixel_idx = 0;
      for (size_t j = 0; j < N_HORIZONTAL_RESOLUTION; j++)
      {            
        for (size_t i = 0; i < N_VERTICAL_RESOLUTION; i++)
        {
            if(i <= seq_offset){
              pixels[pixel_idx] = (i % 3) == 0? 128:0;
              pixels[pixel_idx+1] = (i % 3) == 1? 128:0;
              pixels[pixel_idx+2] = (i % 3) == 2? 128:0;
            }
            
            pixel_idx+=N_CHANNELS_PER_PIXEL;
        }
      }
    } else if (frameNumber < 120+5*N_VERTICAL_RESOLUTION){
      // Fade out and only keep rgb stribes in top 3 rows
      const uint32_t seq_offset = frameNumber - 120 - 4*N_VERTICAL_RESOLUTION;
      uint32_t pixel_idx = 0;
      for (size_t j = 0; j < N_HORIZONTAL_RESOLUTION; j++)
      {            
        for (size_t i = 0; i < N_VERTICAL_RESOLUTION; i++)
        {
            if(i <= seq_offset){
              pixels[pixel_idx] = (i == 0)? 128:0;
              pixels[pixel_idx+1] = (i == 1)? 128:0;
              pixels[pixel_idx+2] = (i == 2)? 128:0;
            }
            
            pixel_idx+=N_CHANNELS_PER_PIXEL;
        }
      }
    }else{
      /// End rendering of init frames
      //printf("Init done.\n");
      return false;
    }
    
    sleep_ms(60);
    return true;
}

int main() {
    // const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    // gpio_init(LED_PIN);
    // gpio_set_dir(LED_PIN, GPIO_OUT);
    // gpio_put(LED_PIN, 1);

    stdio_init_all();
    //sleep_ms(5000);

    LEDController& ledController = LEDController::getInstance();
    SpiDataReader& reader = SpiDataReader::getInstance();

    uint8_t * pixels = ledController.getRenderBuffer();
    memset(pixels,0, N_BUFFER_SIZE);

    if (!watchdog_caused_reboot()){
      uint32_t frameIdx = 0;                              
      while(showNextInitFrame(frameIdx++, pixels)); 
    }
  
    reader.syncWithMaster();
    reader.processData(ledController);

    // while(true);
}
