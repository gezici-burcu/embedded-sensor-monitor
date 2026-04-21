#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>

/**
 * circular buffer interface for filtered sensor data storage
 * Stores filtered sensor values in a fixed-size circular buffer
 * When the buffer is full, the oldest value is overwritten by the newest one.
 */
#define BUFFER_CAPACITY 30

/*
Stores filtered sensor values in a circular buffer.
This buffer is used to keep the latest filtered samples of a sensor
for statistical calculations.
*/
typedef struct{
    float data[BUFFER_CAPACITY];  /**< Buffer data array */
    uint8_t head;                /**< Next write index */
    uint8_t count;               /**< Number of valid elements in the buffer */
    uint8_t capacity;            /**< Maximum buffer capacity */
} circular_buffer_t;

/**
 * Initializes a circular buffer.
 * buffer pointer to buffer structure
 * capacity of the buffer.
*/
void buffer_init(circular_buffer_t *buffer, uint8_t capacity);

/**
 * Pushes a new filtered value into the buffer.
 * If the buffer is full, the oldest value is overwritten.
 * value Filtered sensor value to store.
 */
void buffer_push(circular_buffer_t *buffer, float value);

/**
 * Returns the number of valid elements currently stored in the buffer.
 * Number of stored elements.
 */
uint8_t buffer_get_count (const circular_buffer_t *buffer);

/**
 * Copies valid buffer elements into a linear array in logical order.
 * This function is used before statistical calculations so that the data
 * can be processed as a normal array.
 */
void buffer_copy_to_array(const circular_buffer_t *buffer, float *output_array);

/**
 * Clears the buffer content logically.
 *  The stored values are ignored after clearing, and the write position
 * is reset for the next data collection period.
 */
void buffer_clear(circular_buffer_t *buffer);

#endif