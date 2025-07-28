#include <Wire.h>

#define SLAVE_ADDRESS 0x08        // I2C slave address

const int signalPin = 11;        // Pin connected to the ultrasonic sensor signal
volatile long distanceCm = 0;    // Variable to store the measured distance

void setup() {
  Wire.begin(SLAVE_ADDRESS);     // Initialize I2C as slave with given address
  Wire.onRequest(requestEvent);  // Register event handler for data request from master
  Serial.begin(9600);            // Start serial communication for debugging
}

void loop() {
  // Continuously measure the distance every second
  distanceCm = measureDistance();
  delay(1000);
}

long measureDistance() {
  long time, cm;

  // Trigger the ultrasonic sensor to send a pulse
  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, LOW);
  delayMicroseconds(2);
  digitalWrite(signalPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(signalPin, LOW);

  // Set the pin as input to read the pulse duration
  pinMode(signalPin, INPUT);
  time = pulseIn(signalPin, HIGH);   // Measure the time of the pulse

  // Calculate distance in centimeters based on pulse duration
  cm = time * 0.03431 / 2;
  return cm;
}

void requestEvent() {
  // Send the 4-byte distance value to the master upon request
  Wire.write((byte*)&distanceCm, sizeof(distanceCm));

  // Print the sent distance for debugging
  Serial.print("Sent data to master: ");
  Serial.print(distanceCm);
  Serial.println(" cm");
}
