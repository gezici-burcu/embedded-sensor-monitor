/**
 * get raw data
 * 
 */
#ifndef FILTER_H
#define FILTER_H

#include <stdint.h>

/**
 * Median filter interface for sensor data processing
 * Each sensor uses its own filter state so that previous samples are stored
 * indepently.
 */
#define FILTER_WINDOW_SIZE 3    /*max size of array*/

/**
 * The filter keeps the latest samples in a small window and calculates
 *  the median value of the valid elements in that window.
 */
typedef struct {
    float window[FILTER_WINDOW_SIZE];  /**< Sample window */
    uint8_t window_size;              /**< Active window size */
    uint8_t index;                    /**< Next write index */
    uint8_t count;                    /**< Number of valid samples in the window */
} filter_state_t;

/**
 * Initializes a median filter state.
 * filter pointer to filter state
 */
void filter_init(filter_state_t *filter, uint8_t window_size);

/**
 * Inserts a new raw sensor value into the filter and returns the filtered output.
 * filter Pointer to filter state.
 * raw_sensor_value New raw sensor reading.
 */
float filter_sensor_value(filter_state_t *filter, float raw_sensor_value);

#endif