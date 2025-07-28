# Arduino I2C Distance Sensor with EEPROM Logging

This project implements a simple I2C communication between two Arduino boards:  
- **Slave:** Measures distance using an ultrasonic sensor and sends the data via I2C.  
- **Master:** Receives the distance data, stores the last 10 readings in EEPROM, and can display stored data via serial command.

## Features

- I2C Slave device sending distance measurements as 4-byte values  
- I2C Master device reading data every second and saving it in EEPROM  
- Serial command interface on Master to read stored EEPROM data (`read`)  

## Hardware

- Two Arduino boards
- Ultrasonic sensor connected to the Slave 
- I2C connection: SDA (for data), SCL (for clock)

## Usage

1. Upload the **Slave** code to the Arduino connected to the ultrasonic sensor.  
2. Upload the **Master** code to the other Arduino.  
3. Connect the boards via I2C (SDA, SCL).  
4. Open the Serial Monitor on the Master Arduino.  
5. The Master will request distance data every second and save the last 10 readings.  
6. To read stored data, type `read` in the Serial Monitor and send.

## Code Overview

### Slave

- Measures distance using a pulse signal on `signalPin` (11).  
- Sends the 4-byte long value over I2C when requested by Master.

### Master

- Requests 4 bytes from Slave every second.  
- Stores readings in EEPROM circularly (last 10 values).  
- Prints received distance or saved EEPROM data on command.

## Author

Manuel Dotto - manueldotto28@gmail.com 
