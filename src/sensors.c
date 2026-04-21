#include "../include/sensors.h"
#include <stdint.h>
#include <stdlib.h>

/**
 * This module simulates raw sensor readings because no physical
 * sensor hardware is available in this project.
 */

/**
 * Generates a random float value in the given range.
 * min Minimum value.
 * max Maximum value.
 * float Random value between min and max.
 */
static float generate_random_float(float min, float max)
{
    float scale = (float)rand() / (float)RAND_MAX;
    return min + scale * (max - min);
}

/**
 * Reads raw sensor data for the given sensor.
 *
 * In this project, sensor data is generated as mock environmental data.
 *
 * device_address I2C address of the sensor.
 * sensor_type Type of the sensor to be read.
 * float Raw sensor value.
 */
float i2c_sensor_read(uint8_t device_address, sensor_t sensor_type)
{
    (void)device_address;

    switch (sensor_type)
    {
        case SENSOR_OXYGEN:
            return generate_random_float(19.5f, 21.5f);

        case SENSOR_CO2:
            return generate_random_float(400.0f, 1200.0f);

        case SENSOR_TEMPERATURE:
            return generate_random_float(20.0f, 30.0f);

        default:
            return 0.0f;
    }
}