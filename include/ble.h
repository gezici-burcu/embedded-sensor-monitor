/**
 * This module defines the BLE packet structure that stores
 * the statistical results of all sensors in a single packet.
 */

#ifndef BLE_H
#define BLE_H

#include "stats.h"

typedef struct{
    sensor_stats_t oxygen_stats;    /**< Statistics for oxygen sensor */
    sensor_stats_t co2_stats;       /**< Statistics for CO2 sensor */
    sensor_stats_t temperature_stats; /**< Statistics for temperature sensor */
}ble_packet_t;

/**
 * BLE functionality will be simulated
 * this function mainly prepares the BLE layer interface
 */
void ble_init(void);

/**
 * Sends a BLE packet containing all sensor statistics.
 * packet Pointer to BLE packet structure.
 */
void ble_send_packet(const ble_packet_t *packet);

#endif