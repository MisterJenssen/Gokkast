#include "ReelConfig.hpp"
#include "SignStruct.hpp"
#include "OperatingState.hpp"
#include "Reel.hpp"

#define baudrate  9600

Reel *reel1;

bool initialise_reel = true;
bool reel_running = false;


double degrees_per_step = 360.0 / reel_1_steps_per_rev;
double degrees_per_sign = 360.0 / reel_1_number_of_signs;
SignStruct reel1_signs[16];

void lightGateInterrupt();

void setup()
{  
  Serial.begin(baudrate);

  reel1 = new Reel(reel_1_wire_1_pin, reel_1_wire_2_pin, reel_1_wire_3_pin, reel_1_wire_4_pin, reel_1_light_sensor_pin, reel_1_min_speed, reel_1_max_speed, reel_1_min_acceleration, reel_1_max_acceleration);
  SignConstructor();
}

void loop()
{
  if(initialise_reel)
  {
    reel1->HomeReel();
    initialise_reel = false;
    
    reel_running = true;    
  }
  if(!reel_running)
  {      
    reel1->DisableReel();
  }
  
  
  if (Serial.available()) 
  {
     int tmp_pos = Serial.parseInt(SKIP_ALL, '\n');
     
     if(tmp_pos >= (sizeof(reel1_signs) / sizeof(reel1_signs[0])))
     {
        Serial.println("Only a number between 0 and 15 is accepted");
     }
     else
     {
        int end_pos = tmp_pos * (degrees_per_sign / degrees_per_step);
        Serial.print("end_pos: "); Serial.println(end_pos);
        reel1->MoveTo(end_pos);

        String tmp_string = reel1_signs[tmp_pos].info;
        Serial.print("Sign: "); Serial.println(tmp_string);
        reel1->EnableReel();
     }
   }
  
   reel_running = reel1->Run();
}


void SignConstructor()
{
  reel1_signs[0].symbol =   blue_x;
  reel1_signs[0].position = 0.0;
  reel1_signs[0].info =     "blue x 1";

  reel1_signs[1].symbol =   grape;
  reel1_signs[1].position = 22.5;
  reel1_signs[1].info =     "grape 1";

  reel1_signs[2].symbol =   melon;
  reel1_signs[2].position = 45.0;
  reel1_signs[2].info =     "melon 1";

  reel1_signs[3].symbol =   blue_x;
  reel1_signs[3].position = 67.5;
  reel1_signs[3].info =     "blue x 2";

  reel1_signs[4].symbol =   questionmark;
  reel1_signs[4].position = 90.0;
  reel1_signs[4].info =     "questionmark 1";
  
  reel1_signs[5].symbol =   red_x;
  reel1_signs[5].position = 112.5;
  reel1_signs[5].info =     "red x 1";

  reel1_signs[6].symbol =   blue_x;
  reel1_signs[6].position = 135.0;
  reel1_signs[6].info =     "blue x 3";

  reel1_signs[7].symbol =   grape;
  reel1_signs[7].position = 157.5;
  reel1_signs[7].info =     "grape 2";

  reel1_signs[8].symbol =   blue_x;
  reel1_signs[8].position = 180;
  reel1_signs[8].info =     "blue x 4";

  reel1_signs[9].symbol =   questionmark;
  reel1_signs[9].position = 13;
  reel1_signs[9].info =     "questionmark 2";

  reel1_signs[10].symbol =   grape;
  reel1_signs[10].position = 12;
  reel1_signs[10].info =     "grape 3";

  reel1_signs[11].symbol =   questionmark;
  reel1_signs[11].position = 11;
  reel1_signs[11].info =     "questionmark 3";

  reel1_signs[12].symbol =   grape;
  reel1_signs[12].position = 10;
  reel1_signs[12].info =     "grape 4";
 
  reel1_signs[13].symbol =   berries;
  reel1_signs[13].position = 9;
  reel1_signs[13].info =     "berries 1"; 
  
  reel1_signs[14].symbol =   xtra;
  reel1_signs[14].position = 8;
  reel1_signs[14].info =     "xtra 1";
  
  reel1_signs[15].symbol =   pear;
  reel1_signs[15].position = 7;
  reel1_signs[15].info =     "pear 1";
}
