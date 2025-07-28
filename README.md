# Arduino I2C Distance Sensor with EEPROM Logging (Tinkercad Simulation)

This project demonstrates simple I2C communication between two Arduino boards:  
- **Slave:** Measures distance using an ultrasonic sensor and sends the data via I2C.  
- **Master:** Receives the distance data, stores the last 10 readings in a simulated EEPROM, and can display stored data via serial command.

## Features

- I2C Slave device sending distance measurements as 4-byte values  
- I2C Master device reading data every second and saving it in a simulated EEPROM (using Tinkercad’s EEPROM emulation)  
- Serial command interface on Master to read stored EEPROM data (`read`)  

## Hardware

- Two Arduino Uno boards  
- Ultrasonic sensor connected to the Slave  
- I2C connection: SDA (data line), SCL (clock line)

## Usage

1. Upload the **Slave** code to the Arduino connected to the ultrasonic sensor.  
2. Upload the **Master** code to the other Arduino.  
3. Connect the boards via I2C lines (SDA and SCL).  
4. Open the Serial Monitor on the Master Arduino.  
5. The Master requests distance data every second and stores the last 10 readings in simulated EEPROM.  
6. To read stored data, type `read` in the Serial Monitor and send.

## Code Overview

### Slave

- Measures distance using a pulse signal on `signalPin` (pin 11).  
- Sends the 4-byte long distance value over I2C when requested by the Master.

### Master

- Requests 4 bytes from the Slave every second.  
- Stores readings in EEPROM circularly (last 10 values) — **note:** EEPROM is simulated in Tinkercad and not real hardware EEPROM.  
- Prints received distance or saved EEPROM data on serial command.

---

## Note for Real Hardware Use

- In a real Arduino setup, EEPROM storage is persistent and physically stored in onboard memory.  
- This simulation uses Tinkercad’s EEPROM emulation, which behaves like real EEPROM but is virtual for testing purposes.
- When deploying on physical hardware, be aware of EEPROM wear limits.
