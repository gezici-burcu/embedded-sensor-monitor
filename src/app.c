#include "../include/app.h"
#include "../include/sensors.h"
#include "../include/filter.h"
#include "../include/buffer.h"
#include "../include/stats.h"
#include "../include/ble.h"

/**
 * High-level application logic for the embedded assignment.
 *
 * This module coordinates sensor reading, filtering, buffering,
 * statistics calculation, and BLE packet transmission.
 */

static sensor_config_t sensor_list[3] =
{
    {SENSOR_OXYGEN, 0x73, "Oxygen"},
    {SENSOR_CO2, 0x62, "CO2"},
    {SENSOR_TEMPERATURE, 0x48, "Temperature"}
};

static filter_state_t oxygen_filter;
static filter_state_t co2_filter;
static filter_state_t temperature_filter;

static circular_buffer_t oxygen_buffer;
static circular_buffer_t co2_buffer;
static circular_buffer_t temperature_buffer;

static uint8_t cycle_counter = 0;

/**
 * Initializes the application state.
 */
void app_init(void)
{
    filter_init(&oxygen_filter, FILTER_WINDOW_SIZE);
    filter_init(&co2_filter, FILTER_WINDOW_SIZE);
    filter_init(&temperature_filter, FILTER_WINDOW_SIZE);

    buffer_init(&oxygen_buffer, BUFFER_CAPACITY);
    buffer_init(&co2_buffer, BUFFER_CAPACITY);
    buffer_init(&temperature_buffer, BUFFER_CAPACITY);

    ble_init();

    cycle_counter = 0;
}

/**
 * Executes one application cycle.
 *
 * One cycle represents one 1-second sampling period.
 */
void app_run_cycle(void)
{
    sensor_sample_t oxygen_sample;
    sensor_sample_t co2_sample;
    sensor_sample_t temperature_sample;

    oxygen_sample.type = SENSOR_OXYGEN;
    oxygen_sample.raw_value = i2c_sensor_read(sensor_list[0].i2c_address, sensor_list[0].type);
    oxygen_sample.filtered_value = filter_sensor_value(&oxygen_filter, oxygen_sample.raw_value);
    buffer_push(&oxygen_buffer, oxygen_sample.filtered_value);

    co2_sample.type = SENSOR_CO2;
    co2_sample.raw_value = i2c_sensor_read(sensor_list[1].i2c_address, sensor_list[1].type);
    co2_sample.filtered_value = filter_sensor_value(&co2_filter, co2_sample.raw_value);
    buffer_push(&co2_buffer, co2_sample.filtered_value);

    temperature_sample.type = SENSOR_TEMPERATURE;
    temperature_sample.raw_value = i2c_sensor_read(sensor_list[2].i2c_address, sensor_list[2].type);
    temperature_sample.filtered_value = filter_sensor_value(&temperature_filter, temperature_sample.raw_value);
    buffer_push(&temperature_buffer, temperature_sample.filtered_value);

    cycle_counter++;

    if (cycle_counter >= 30)
    {
        float oxygen_values[BUFFER_CAPACITY];
        float co2_values[BUFFER_CAPACITY];
        float temperature_values[BUFFER_CAPACITY];

        sensor_stats_t oxygen_stats;
        sensor_stats_t co2_stats;
        sensor_stats_t temperature_stats;

        ble_packet_t packet;

        buffer_copy_to_array(&oxygen_buffer, oxygen_values);
        buffer_copy_to_array(&co2_buffer, co2_values);
        buffer_copy_to_array(&temperature_buffer, temperature_values);

        oxygen_stats = calculate_stats(oxygen_values, buffer_get_count(&oxygen_buffer));
        co2_stats = calculate_stats(co2_values, buffer_get_count(&co2_buffer));
        temperature_stats = calculate_stats(temperature_values, buffer_get_count(&temperature_buffer));

        packet.oxygen_stats = oxygen_stats;
        packet.co2_stats = co2_stats;
        packet.temperature_stats = temperature_stats;

        ble_send_packet(&packet);

        buffer_clear(&oxygen_buffer);
        buffer_clear(&co2_buffer);
        buffer_clear(&temperature_buffer);

        cycle_counter = 0;
    }
}