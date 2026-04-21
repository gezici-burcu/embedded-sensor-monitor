/**
 * Median filter implementation for sensor data.
 * * This module keeps a small window of recent samples for each sensor
 * and returns the median of the valid values in the window.
 */
#include "../include/filter.h"
#include <stdint.h>

/**
 * A simple bubble sort is used because the window size is very small.
 * values array to sort
 * count Number of valid elements in the array.
 */
static void sort_array(float *values, uint8_t count){
    uint8_t i;
    uint8_t j;

    for(i=0; i<count; i++){
        for(j=0; j<count-1; j++){
            if (values[j] > values[j + 1])
            {
                float temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
            }
        }
    }
}

/**
 * Calculates the median of the valid values in the filter window.
 */
static float calculate_median(const filter_state_t *filter)
{
    float temp[FILTER_WINDOW_SIZE];
    uint8_t i;

    for (i = 0; i < filter->count; i++)
    {
        temp[i] = filter->window[i];
    }

    sort_array(temp, filter->count);

    if (filter->count % 2 == 1)
    {
        return temp[filter->count / 2];
    }
    else
    {
        uint8_t mid = filter->count / 2;
        return (temp[mid - 1] + temp[mid]) / 2.0f;
    }
}

/**
 * Initializes a median filter state.
 */
void filter_init(filter_state_t *filter, uint8_t window_size)
{
    uint8_t i;

    filter->window_size = window_size;
    filter->index = 0;
    filter->count = 0;

    for (i = 0; i < FILTER_WINDOW_SIZE; i++)
    {
        filter->window[i] = 0.0f;
    }
}

/**
 * Inserts a new raw sensor value into the filter 
 * and returns the filtered output. 
 */
float filter_sensor_value(filter_state_t *filter, float raw_sensor_value)
{
    filter->window[filter->index] = raw_sensor_value;
    filter->index = (filter->index + 1) % filter->window_size;

    if (filter->count < filter->window_size)
    {
        filter->count++;
    }

    return calculate_median(filter);
}