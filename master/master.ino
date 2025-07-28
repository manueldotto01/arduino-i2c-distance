#include <Wire.h>
#include <EEPROM.h>

#define SLAVE_ADDRESS 0x08   // I2C slave address

const int maxSamples = 10;  // Maximum number of samples to store in EEPROM
int eepromIndex = 0;        // Current EEPROM write index

void setup() {
  Serial.begin(9600);
  Wire.begin();             // Initialize I2C
  Serial.println("Master ready. Type 'read' to print EEPROM data.");
}

void loop() {
  // Request 4 bytes (long) from slave
  Wire.requestFrom(SLAVE_ADDRESS, (uint8_t)4);

  long distance = 0;
  byte* p = (byte*)&distance;

  // Read the 4 bytes into the long variable
  for (int i = 0; i < 4 && Wire.available(); i++) {
    p[i] = Wire.read();
  }

  // Store the received distance value into EEPROM
  EEPROM.put(eepromIndex * sizeof(long), distance);
  eepromIndex = (eepromIndex + 1) % maxSamples;  // Wrap around index

  delay(1000);

  // Check for serial commands
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "read") {
      Serial.println("Stored data in EEPROM:");
      // Read and print all stored values from EEPROM
      for (int i = 0; i < maxSamples; i++) {
        long value;
        EEPROM.get(i * sizeof(long), value);
        Serial.print(i);
        Serial.print(": ");
        Serial.print(value);
        Serial.println(" cm");
      }
    }
  }
}
