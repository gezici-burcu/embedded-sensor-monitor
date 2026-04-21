# Embedded Sensor Data Processing System

## Overview
This project simulates an embedded system that reads data from multiple sensors, processes the data using filtering techniques, stores it in buffers, calculates statistical values, and transmits the results via a simulated BLE packet.

The system is designed using a modular architecture to mimic real-world embedded software design practices.

---

## Features
- Multi-sensor data acquisition (Oxygen, CO2, Temperature)
- Median filtering for noise reduction
- Circular buffer implementation for data storage
- Statistical analysis:
  - Minimum
  - Maximum
  - Median
  - Standard deviation
- BLE packet simulation (console output)
- Fully modular and scalable architecture

---

## System Architecture

The system follows a layered design:



### Data Flow
1. Sensor data is read (mock implementation)
2. Median filter is applied
3. Filtered data is stored in circular buffers
4. Every 30 seconds:
   - Statistics are calculated
   - Data is packed into a single BLE packet
   - Packet is transmitted (simulated)

---

## Sensors Used

| Sensor Type  | Model                     | I2C Address |
|-------------|--------------------------|------------|
| Oxygen       | DFRobot SEN0322          | 0x73       |
| CO2          | Sensirion SCD41          | 0x62       |
| Temperature  | TI TMP117                | 0x48       |

---

## Project Structure



---

## How It Works

- The system runs in a loop where each iteration represents **1 second**
- Sensor values are generated using mock data
- Every sensor has its own:
  - Filter
  - Buffer
- After **30 cycles (30 seconds)**:
  - Data is analyzed
  - Results are sent as a single BLE packet

---

## Example Output



---

## Notes

- No physical sensors were used
- I2C communication is simulated
- BLE transmission is simulated via console output
- Designed for learning embedded system architecture

---

## References

- DFRobot Oxygen Sensor (SEN0322)
- Sensirion SCD41 CO2 Sensor
- Texas Instruments TMP117 Temperature Sensor
- General signal processing and statistical methods

---

## Author
Burcu Gezici