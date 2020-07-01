#include <AccelStepper.h>

#define stepper_wire_1  8
#define stepper_wire_2  9
#define stepper_wire_3  10
#define stepper_wire_4  11

long end_position = 0;

AccelStepper stepper(AccelStepper::FULL4WIRE, stepper_wire_1, stepper_wire_2, stepper_wire_3, stepper_wire_4, true); // 2 wires (driver), direction and step


void setup()
{  
 Serial.begin(9600);
  
  pinMode(stepper_wire_1, OUTPUT);
  pinMode(stepper_wire_2, OUTPUT);
  pinMode(stepper_wire_3, OUTPUT);
  pinMode(stepper_wire_4, OUTPUT);

  stepper.setMaxSpeed(150); // steps/s
  stepper.setAcceleration(20); // steps/s/s
}

void loop()
{
    if (Serial.available()) 
    {
      end_position = Serial.parseInt(SKIP_ALL, '\n');
      stepper.moveTo(end_position);
      Serial.println(end_position);
    }
  
    stepper.run();
}
