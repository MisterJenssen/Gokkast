#include <AccelStepper.h>
#include "SignStruct.hpp"

#define stepper_wire_1  8
#define stepper_wire_2  9
#define stepper_wire_3  10
#define stepper_wire_4  11

#define min_speed         30    //steps/s
#define max_speed         300   //steps/s
#define max_acceleration  100   //steps/s/s

long end_position = 0;

SignStruct signs[16];


AccelStepper stepper(AccelStepper::HALF4WIRE, stepper_wire_1, stepper_wire_2, stepper_wire_3, stepper_wire_4, true); // 2 wires (driver), direction and step


void setup()
{  
 Serial.begin(9600);
  
  pinMode(stepper_wire_1, OUTPUT);
  pinMode(stepper_wire_2, OUTPUT);
  pinMode(stepper_wire_3, OUTPUT);
  pinMode(stepper_wire_4, OUTPUT);

  stepper.setMaxSpeed(max_speed); 
  stepper.setAcceleration(max_acceleration); 
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

void SignConstructor()
{
  signs[0].symbol =   red_x;
  signs[0].position = 1;
  signs[0].info =     "red x 1";

  signs[1].symbol =   questionmark;
  signs[1].position = 2;
  signs[1].info =     "questionmark 1";

  signs[2].symbol =   blue_x;
  signs[2].position = 3;
  signs[2].info =     "blue x 1";

  signs[3].symbol =   melon;
  signs[3].position = 4;
  signs[3].info =     "melon 1";

  signs[4].symbol =   grape;
  signs[4].position = 5;
  signs[4].info =     "grape 1";

  signs[5].symbol =   blue_x;
  signs[5].position = 6;
  signs[5].info =     "blue x 2";

  signs[6].symbol =   pear;
  signs[6].position = 7;
  signs[6].info =     "pear 1";

  signs[7].symbol =   xtra;
  signs[7].position = 8;
  signs[7].info =     "xtra 1";

  signs[8].symbol =   berries;
  signs[8].position = 9;
  signs[8].info =     "berries 1";

  signs[9].symbol =   grape;
  signs[9].position = 10;
  signs[9].info =     "grape 2";

  signs[10].symbol =   questionmark;
  signs[10].position = 11;
  signs[10].info =     "questionmark 2";

  signs[11].symbol =   grape;
  signs[11].position = 12;
  signs[11].info =     "grape 3";

  signs[12].symbol =   questionmark;
  signs[12].position = 13;
  signs[12].info =     "questionmark 3";

  signs[13].symbol =   blue_x;
  signs[13].position = 14;
  signs[13].info =     "blue x 3";

  signs[14].symbol =   grape;
  signs[14].position = 15;
  signs[14].info =     "grape 4";

  signs[15].symbol =   blue_x;
  signs[15].position = 16;
  signs[15].info =     "blue x 4";
}
