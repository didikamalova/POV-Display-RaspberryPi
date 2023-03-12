#include <stdio.h>
#include <cmath>

#include "RTTMeasure.hpp"

// This file measures ROUND TRIP TIME (RTT)
// RTTmeasure
// Hall sensor code!
// They use 8 magnets - which they store in N_MAGNETS - this code should be translatable, by
// changing this constant in the header file.

// generally they define segments as which out of the 8 magents the LED strip is over
// therefore, opposite segment is defined as the size of the circular frame, opposite to 
// the side of the frame the hall sensor is on.

// they also define N_COLUMNS_PER_SEGMENT - which is the number of columns that are displayed while running over a magnet

uint32_t RTTMeasure::m_measured_intervals[N_MAGNETS] = {};
int8_t RTTMeasure::m_curr_segment_index = 0;
critical_section_t RTTMeasure::critical_section = {};
absolute_time_t RTTMeasure::m_last_hall_sensor_event = nil_time;
absolute_time_t RTTMeasure::m_last_print = nil_time;

RTTMeasure::RTTMeasure()
{
    init(); // initializes to find speed and enables interrupts
    gpio_set_irq_enabled_with_callback(PIN_HALL_SENSOR, GPIO_IRQ_EDGE_RISE, true, &RTTMeasure::gpio_hall_sensor_callback);
}

RTTMeasure::~RTTMeasure()
{
}

void RTTMeasure::init(){
    for (size_t i = 0; i < N_MAGNETS; i++)
    {
        m_measured_intervals[i] = get_absolute_time();
    }
    m_curr_segment_index = 0;
    m_last_hall_sensor_event = nil_time;

    critical_section_init(&critical_section);
}

RTTMeasure& RTTMeasure::getInstance() {
    static RTTMeasure instance;
    return instance;
}


// I believe they have a struct (sort of) called critical section
// note: segments is essentially no of magnets
// this tracks curr_segment_index, which is the current segment index that the frame is in
// they also have opposite_segment_index which tracks the segment the opposite side of the frame is in
// tracks the last_hall_sensor_event time
// tracks the expected segment time which they calculated during intialization - amount of time spent in each section
// also tracks the expected segmente time for opposite side segment

// this fills the critcal section list/array/struct
void RTTMeasure::gpio_hall_sensor_callback(uint gpio, uint32_t events) {
    const absolute_time_t curr_time = get_absolute_time();
    if (gpio != PIN_HALL_SENSOR)
        return;
    
    const uint32_t old_dt = m_measured_intervals[m_curr_segment_index];
    critical_section_enter_blocking(&critical_section);
    if (!is_nil_time(m_last_hall_sensor_event)){
        const uint32_t new_dt = absolute_time_diff_us(m_last_hall_sensor_event, curr_time);
        m_measured_intervals[m_curr_segment_index] = 0.5* new_dt + 0.5*old_dt; // avg of new and old times, one full trip time
    }
    m_last_hall_sensor_event = curr_time;
	// finds current segment index
    m_curr_segment_index = (m_curr_segment_index + 1U) % N_MAGNETS; // 1 u is unsigned 1
    critical_section_exit(&critical_section);
}

// one all of the crtical section is filled

// the code must work out the details for the columns of the LEDs themselves based on the number
// of columns they calculated fits in a segment which is based on the size of the magnet
// the code can track the number of columns that have had their LEDs driven per segment and same with the opposite segment columns


// this column information can be used to work out the column number to drive if we are constantly
//incrementing every time we need to drive a column?
