#include <Joystick.h>
#include <Wire.h>
#include <AS5600.h>

// Joystick object definition
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_MULTI_AXIS, 2, 0,
                   false, false, false, false, false, false,
                   true, false, false, false, false);

AS5600 as5600;  // Object for the AS5600 sensor

const int button1Pin = 4;    // Pin for button 1 (e.g., digital pin 4)
const int button2Pin = 5;    // Pin for button 2 (e.g., digital pin 5)

// Minimum and maximum values obtained from the AS5600 sensor
const int minSensorValue = 2008;
const int maxSensorValue = 1232;

void setup() {
  Wire.begin();        // Initialize I2C communication
  as5600.begin();      // Initialize the AS5600 sensor
  
  pinMode(button1Pin, INPUT_PULLUP);  // Configure the pin for button 1
  pinMode(button2Pin, INPUT_PULLUP);  // Configure the pin for button 2
  
  Joystick.begin();    // Initialize the Joystick library
}

void loop() {
  // Read the value from the AS5600 sensor
  int valorAS5600 = as5600.readAngle();  // Read the angle from the AS5600 sensor in degrees

  // Calculate the mapped value based on the maximum range of 72 degrees
  int mappedRudder = map(valorAS5600, minSensorValue, maxSensorValue, 0, 1023);  // Map to joystick range (1200-2020 to 0-1023)

  // Set the rudder value
  Joystick.setRudder(mappedRudder);

  // Read the state of the buttons and update them on the joystick
  int buttonState1 = !digitalRead(button1Pin);  // Invert the value due to pull-up
  int buttonState2 = !digitalRead(button2Pin);  // Invert the value due to pull-up
  
  Joystick.setButton(0, buttonState1);  // Set the state of button 1
  Joystick.setButton(1, buttonState2);  // Set the state of button 2
  
  delay(10);  // Small delay to avoid excessive readings
}
