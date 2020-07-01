
/*
 Stepper Motor Control - one revolution

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.


 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe

 */

#include <Stepper.h>

int currentSpeed = 0;
const int maxRpm = 300;
const int minRpm = 30;
const int stepsPerRevolution = 48;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() 
{
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() 
{
  currentSpeed = minRpm;
  while(currentSpeed < maxRpm)
  { 
    Serial.println(currentSpeed);
    myStepper.setSpeed(currentSpeed); 
    myStepper.step(10);
    currentSpeed += 5;
  }

  // step one revolution  in one direction:
  myStepper.step(4 * stepsPerRevolution);
  
  while(currentSpeed >= minRpm)
  { 
    Serial.println(currentSpeed);
    myStepper.setSpeed(currentSpeed); 
    myStepper.step(10);
    currentSpeed -= 5;
  }
  
  delay(4000);
}
