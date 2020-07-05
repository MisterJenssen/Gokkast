#include <AccelStepper.h>

#define stepper_wire_1  8
#define stepper_wire_2  9
#define stepper_wire_3  10
#define stepper_wire_4  11

#define light_gate_pin  2

#define end_position      1000  //steps
#define min_speed         30    //steps/s
#define max_speed         300   //steps/s
#define max_acceleration  100   //steps/s/s

AccelStepper stepper(AccelStepper::HALF4WIRE, stepper_wire_1, stepper_wire_2, stepper_wire_3, stepper_wire_4, true); // 2 wires (driver), direction and step
void lightGateInterrupt();

void setup()
{  
 Serial.begin(9600);
  
  pinMode(stepper_wire_1, OUTPUT);
  pinMode(stepper_wire_2, OUTPUT);
  pinMode(stepper_wire_3, OUTPUT);
  pinMode(stepper_wire_4, OUTPUT);
  pinMode(light_gate_pin, INPUT);

  attachInterrupt(digitalPinToInterrupt(light_gate_pin), lightGateInterrupt, CHANGE);

  stepper.setMaxSpeed(max_speed);
  stepper.setAcceleration(max_acceleration);

  //stepper.setSpeed(250);
  stepper.moveTo(end_position);
}

void loop()
{
    if (stepper.distanceToGo() == 0) // If at the end of travel go to the other end
    {
      delay(2000);
      stepper.moveTo(-stepper.currentPosition());
    }
    stepper.run();


    if (Serial.available()) 
    {
      char inChar = (char)Serial.read();
      if(inChar=='S') 
      {
        stepper.stop();
        stepper.disableOutputs();
        Serial.println(stepper.currentPosition());
        while(true);
      }
    }   
}

void lightGateInterrupt()
{
    int value = digitalRead(light_gate_pin);
    Serial.print("Value: ");
    Serial.println(value);
}
