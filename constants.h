// define all important constants


#define VERTICAL_RESOLUTION 60 // no. of LEDs on each side
#define HORIZONTAL_RESOLUTION 120 // calculate this by doing math - circumference of circular frame/width of LED strip
#define CHANNELS_PER_PIXEL 4 // ABGR

#define NUM_MAGNETS 6

#define NUM_PIXELS (VERTICAL_RESOLUTION*HORIZONTAL_RESOLUTION) // size in pixels/LEDs
#define BUFFER_SIZE_PER_COLUMN (VERTICAL_RESOLUTION*CHANNELS_PER_PIXEL)
#define BUFFER_SIZE (NUM_PIXELS*CHANNELS_PER_PIXEL) // buffer size in bytes
