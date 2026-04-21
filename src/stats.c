/*Statistical analysis implementation for filtered sensor data.*/
#include "../include/stats.h"
#include <math.h>
#include <stdint.h>

/**
 * Sorts an array in ascending order.
 * A simple bubble sort is used because the data size is small.
 */
static void sort_array(float *values, uint8_t count)
{
    uint8_t i;
    uint8_t j;
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count - 1; j++)
        {
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
 * Calculates the minimum value in an array.
 */
static float calculate_min(const float *values, uint8_t count)
{
    uint8_t i;
    float min_value = values[0];

    for (i = 1; i < count; i++)
    {
        if (values[i] < min_value)
        {
            min_value = values[i];
        }
    }

    return min_value;
}
/**
 * Calculates the maximum value in an array.
 */
static float calculate_max(const float *values, uint8_t count)
{
    uint8_t i;
    float max_value = values[0];

    for (i = 1; i < count; i++)
    {
        if (values[i] > max_value)
        {
            max_value = values[i];
        }
    }

    return max_value;
}
/**
 * Calculates the median value in an array.
 */
static float calculate_median(const float *values, uint8_t count)
{
    float temp[30];
    uint8_t i;

    for (i = 0; i < count; i++)
    {
        temp[i] = values[i];
    }

    sort_array(temp, count);

    if (count % 2 == 1)
    {
        return temp[count / 2];
    }
    else
    {
        uint8_t mid = count / 2;
        return (temp[mid - 1] + temp[mid]) / 2.0f;
    }
}
/*Calculates the standard deviation of an array*/
static float calculate_std_dev(const float *values, uint8_t count)
{
    uint8_t i;
    float mean = 0.0f;
    float variance = 0.0f;

    for (i = 0; i < count; i++)
    {
        mean += values[i];
    }

    mean /= count;

    for (i = 0; i < count; i++)
    {
        float diff = values[i] - mean;
        variance += diff * diff;
    }

    variance /= count;

    return sqrtf(variance);
}
/*Calculates statistics for a given sensor data array.*/
sensor_stats_t calculate_stats(const float *values, uint8_t count)
{
    sensor_stats_t stats = {0};

    if (count == 0)
    {
        return stats;
    }

    stats.min = calculate_min(values, count);
    stats.max = calculate_max(values, count);
    stats.median = calculate_median(values, count);
    stats.std_dev = calculate_std_dev(values, count);

    return stats;
}