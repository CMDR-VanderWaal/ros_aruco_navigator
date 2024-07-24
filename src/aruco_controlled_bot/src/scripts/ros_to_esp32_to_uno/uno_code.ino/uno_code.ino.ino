#include <Wire.h>
#include <AFMotor.h>

AF_DCMotor motor1(2); // Motor connected to M1 port of Adafruit Motor Shield
AF_DCMotor motor2(3); // Motor connected to M2 port of Adafruit Motor Shield

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Serial.begin(9600);           // start serial for output
  Wire.onReceive(receiveEvent); // register event
  Serial.println("Ready!");
}

void loop() {
  // Nothing to do here
}
void receiveEvent(int howMany) {
  if (Wire.available()) { // Check if data is available
    char c = Wire.read(); // receive byte as a character

    // Print the received command
    Serial.print("Received command: ");
    Serial.println(c);

      motor1.setSpeed(255); // Set motor speed
      motor1.run(FORWARD);  // Run motor in forward direction
      motor2.setSpeed(255); // Set motor speed
      motor2.run(FORWARD);  // Run motor in forward direction
    // Execute the command
    if (c == 'F') {
      motor1.setSpeed(255); // Set motor speed
      motor1.run(FORWARD);  // Run motor in forward direction
      motor2.setSpeed(255); // Set motor speed
      motor2.run(FORWARD);  // Run motor in forward direction
    } 
    else if (c == 'B') {
      motor1.setSpeed(255); // Set motor speed
      motor1.run(BACKWARD); // Run motor in backward direction
      motor2.setSpeed(255); // Set motor speed
      motor2.run(BACKWARD); // Run motor in backward direction
    } 
    else if (c == 'R') {
      motor1.setSpeed(255); // Set motor speed
      motor1.run(FORWARD);  // Run motor in forward direction
      motor2.setSpeed(255); // Set motor speed
      motor2.run(BACKWARD); // Run motor in backward direction
    } 
    else if (c == 'L') {
      motor1.setSpeed(255); // Set motor speed
      motor1.run(BACKWARD); // Run motor in backward direction
      motor2.setSpeed(255); // Set motor speed
      motor2.run(FORWARD);  // Run motor in forward direction
    }
    else if (c == 'S') {
      motor1.setSpeed(0); // Stop motor
      motor1.run(RELEASE);
      motor2.setSpeed(0); // Stop motor
      motor2.run(RELEASE);
    }
  }
}