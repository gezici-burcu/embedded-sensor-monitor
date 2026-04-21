/*
 * This module manages the high-level application logic including
 * sensor reading, filtering, buffering, statistics calculation,
 * and BLE packet transmission.
*/
#ifndef APP_H
#define APP_H


/**
 * This function prepares sensor configurations, filter states,
 * circular buffers, BLE module, and internal counters.
 */
void app_init(void);

/**
 * One cycle represents one 1-second sampling period.
 * During each cycle, all sensors are read, filtered values are stored,
 * and every 30 cycles the statistical results are sent in one BLE packet.
 */
void app_run_cycle(void);

#endif