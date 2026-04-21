#include "../include/ble.h"
#include <stdio.h>

/**
 Simulated BLE transmission implementation.
 *
 * This module simulates BLE packet transmission by printing
 * the packet content to the console.
 */

/**
 * In this simulated project, no real BLE hardware is used,
 * so this function only prints an initialization message.
 */
void ble_init(void)
{
    printf("BLE module initialized.\n");
}

/**
 *Sends a BLE packet containing all sensor statistics.
 * BLE transmission is simulated by printing
 * the packet content in a readable format.
 *
 * packet Pointer to BLE packet structure.
 */
void ble_send_packet(const ble_packet_t *packet)
{
    if (packet == NULL)
    {
        return;
    }

    printf("\n========== BLE PACKET ==========\n");

    printf("OXYGEN STATS:\n");
    printf("  Min     : %.2f\n", packet->oxygen_stats.min);
    printf("  Max     : %.2f\n", packet->oxygen_stats.max);
    printf("  Median  : %.2f\n", packet->oxygen_stats.median);
    printf("  Std Dev : %.2f\n", packet->oxygen_stats.std_dev);

    printf("\nCO2 STATS:\n");
    printf("  Min     : %.2f\n", packet->co2_stats.min);
    printf("  Max     : %.2f\n", packet->co2_stats.max);
    printf("  Median  : %.2f\n", packet->co2_stats.median);
    printf("  Std Dev : %.2f\n", packet->co2_stats.std_dev);

    printf("\nTEMPERATURE STATS:\n");
    printf("  Min     : %.2f\n", packet->temperature_stats.min);
    printf("  Max     : %.2f\n", packet->temperature_stats.max);
    printf("  Median  : %.2f\n", packet->temperature_stats.median);
    printf("  Std Dev : %.2f\n", packet->temperature_stats.std_dev);

    printf("================================\n");
}