# Wiring Reference

## Components & Pin Connections

| Target Component | Component Pin | Connects To | ESP32 Pin |
|---|---|---|---|
| **ESP32 (Main Board)** | 3V3 | → | 3.3V Rail |
| | GND | → | GND Rail |
| **MPU-6050 (Sensor)** | VCC | → | 3.3V Rail |
| | GND | → | GND Rail |
| | SCL | → | D22 |
| | SDA | → | D21 |
| **LED 1 (Far Left)** | Anode (Long leg) | → Resistor → | D13 |
| **LED 2 (Left)** | Anode (Long leg) | → Resistor → | D12 |
| **LED 3 (Center)** | Anode (Long leg) | → Resistor → | D14 |
| **LED 4 (Right)** | Anode (Long leg) | → Resistor → | D27 |
| **LED 5 (Far Right)** | Anode (Long leg) | → Resistor → | D26 |
| **All LEDs** | Cathodes (Short legs) | → | GND Rail |

## Notes

- All LED anodes connect through a current-limiting **resistor** before the ESP32 GPIO pin.
- All LED cathodes share a common **GND rail** connection.
- The MPU-6050 communicates via **I2C** (SDA on D21, SCL on D22).
- The ESP32 3.3V output powers both the sensor rail and the logic level.
