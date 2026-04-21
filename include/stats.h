/**
 * Statistical analysis interface for filtered sensor data.
 * calculates min, max,median, standard deviation from array 
 * of filtered sensor samples
 */
#ifndef STATS_H
#define STATS_H

#include <stdint.h>

/**
 * Stores statistical results for a sensor data set.
 */
typedef struct{
    float min;      /**< Minimum value */
    float max;      /**< Maximum value */
    float median;   /**< Median value */
    float std_dev;  /**< Standard deviation */
}sensor_stats_t;

/**
 * Calculates statistics for a given sensor data array.
 * values Input array containing filtered sensor values.
 * count Number of valid elements in the array.
 */
sensor_stats_t calculate_stats(const float *values, uint8_t count);


#endif