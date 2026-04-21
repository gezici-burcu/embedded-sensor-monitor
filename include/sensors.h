/**
 * Dosya içeriği:
 * sensor_t, sensor_config_t, sensor_sample_t, i2c_sensor_read(...)
 * Bu modül, sensör konfigürasyonlarını ve sensör okuma arayüzünü tanımlar.
 * Mock veri üretimi kullanılacaktır.
 */
#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h> //to use uint8_t

/**
 * This enum is used to identify which sensor is being processed.
 */
typedef enum
{
    SENSOR_OXYGEN = 0,
    SENSOR_CO2,
    SENSOR_TEMPERATURE
} sensor_t;


/**
 * sensor_config_t struct
 * stores static configuration information for a sensor.
*/
typedef struct{
    sensor_t type;       /**< Type of the sensor */
    uint8_t i2c_address;    /**< I2C address of the sensor */
    const char *name;        /**< Sensor name */
}sensor_config_t;

/**
 * stores one sensor sample including raw and filtered values
 */
typedef struct{
    sensor_t type;
    float raw_value;
    float filtered_value;
}sensor_sample_t;

/**
 *Reads raw sensor data for the given sensor.
 *
 * In this project, the implementation will return mock sensor data
 * because no physical sensor hardware is available.
 *
 * device_address I2C address of the sensor.
 *  sensor_type Type of the sensor to be read.
 * return float Raw sensor value.
 */
float i2c_sensor_read(uint8_t device_address, sensor_t sensor_type);

#endif