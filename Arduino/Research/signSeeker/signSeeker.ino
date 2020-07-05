#include "ReelConfig.hpp"
#include "SignStruct.hpp"
#include "OperatingState.hpp"
#include "Reel.hpp"

#define baudrate  9600

Reel *reel1;

long end_position = 0;
bool initialise = true;

SignStruct signs[16];

void lightGateInterrupt();

void setup()
{  
  Serial.begin(baudrate);

  reel1 = new Reel(reel_1_wire_1_pin, reel_1_wire_2_pin, reel_1_wire_3_pin, reel_1_wire_4_pin, reel_1_light_sensor_pin, reel_1_min_speed, reel_1_max_speed, reel_1_min_acceleration, reel_1_max_acceleration);
  
  attachInterrupt(digitalPinToInterrupt(reel_1_light_sensor_pin), lightGateInterrupt, FALLING);
}

void loop()
{
  if(initialise)
  {
    reel1->EnableReel();
    initialise = false;
  }
  
  if (Serial.available()) 
  {
     end_position = Serial.parseInt(SKIP_ALL, '\n');
     reel1->MoveTo(end_position);
     Serial.println(end_position);
   }
  
   reel1->Run();
}

void lightGateInterrupt()
{
  Serial.println("In interrupt");
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
