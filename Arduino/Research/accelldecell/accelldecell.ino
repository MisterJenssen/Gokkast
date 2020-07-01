#include <AccelStepper.h>

#define stepper_wire_1  8
#define stepper_wire_2  9
#define stepper_wire_3  10
#define stepper_wire_4  11

#define end_position    1000

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

  //stepper.setSpeed(250);
  stepper.moveTo(end_position);
}

void loop()
{
    if (stepper.distanceToGo() == 0) // If at the end of travel go to the other end
    {
      delay(1000);
      stepper.moveTo(-stepper.currentPosition());
    }
    stepper.run();


    if (Serial.available()) 
    {
      char inChar = (char)Serial.read();
      if(inChar=='S') 
      {
        stepper.stop();
        Serial.println(stepper.currentPosition());
        while(true);
      }
    }   
}
