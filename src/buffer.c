/**
 * Circular buffer implementation for filtered sensor data.
 */
#include "../include/buffer.h"

void buffer_init(circular_buffer_t *buffer, uint8_t capacity)
{
    uint8_t i;

    buffer->head = 0;
    buffer->count = 0;
    buffer->capacity = capacity;

    for (i = 0; i < BUFFER_CAPACITY; i++)
    {
        buffer->data[i] = 0.0f;
    }
}

/**
 * Pushes a new filtered value into the buffer.
 * If the buffer is full, the oldest value is overwritten.
 */
void buffer_push(circular_buffer_t *buffer, float value)
{
    buffer->data[buffer->head] = value;
    buffer->head = (buffer->head + 1) % buffer->capacity;

    if (buffer->count < buffer->capacity)
    {
        buffer->count++;
    }
}
/**
 *  Returns the number of valid elements currently stored in the buffer.
 */
uint8_t buffer_get_count(const circular_buffer_t *buffer)
{
    return buffer->count;
}
/**
 * Copies valid buffer elements into a linear array in logical order.
 */
void buffer_copy_to_array(const circular_buffer_t *buffer, float *output_array)
{
    uint8_t i;
    uint8_t start_index;

    if (buffer->count < buffer->capacity)
    {
        start_index = 0;
    }
    else
    {
        start_index = buffer->head;
    }

    for (i = 0; i < buffer->count; i++)
    {
        output_array[i] = buffer->data[(start_index + i) % buffer->capacity];
    }
}
/**
 * Clears the buffer content logically.
 */
void buffer_clear(circular_buffer_t *buffer)
{
    buffer->head = 0;
    buffer->count = 0;
}

