#include "ReelConfig.hpp"
#include "SignStruct.hpp"
#include "OperatingState.hpp"
#include "Reel.hpp"

#define baudrate  9600

Reel *reel1;
Reel *reel2;
Reel *reel3;

int random_number1;
int random_number2;
int random_number3;

bool initialise_reel = true;
bool reels_running = false;

double degrees_per_step = 360.0 / reel_1_steps_per_rev;
double degrees_per_sign = 360.0 / reel_1_number_of_signs;
SignStruct reel1_signs[16];
SignStruct reel2_signs[16];
SignStruct reel3_signs[16];

void setup()
{
  Serial.begin(baudrate);

  randomSeed(analogRead(0));

  reel1 = new Reel(reel_1_wire_1_pin, reel_1_wire_2_pin, reel_1_wire_3_pin, reel_1_wire_4_pin, reel_1_light_sensor_pin, reel_1_min_speed, reel_1_max_speed, reel_1_min_acceleration, reel_1_max_acceleration);
  reel2 = new Reel(reel_2_wire_1_pin, reel_2_wire_2_pin, reel_2_wire_3_pin, reel_2_wire_4_pin, reel_2_light_sensor_pin, reel_2_min_speed, reel_2_max_speed, reel_2_min_acceleration, reel_2_max_acceleration);
  reel3 = new Reel(reel_3_wire_1_pin, reel_3_wire_2_pin, reel_3_wire_3_pin, reel_3_wire_4_pin, reel_3_light_sensor_pin, reel_3_min_speed, reel_3_max_speed, reel_3_min_acceleration, reel_3_max_acceleration);

  SignConstructor();
}

void loop()
{
  if (initialise_reel)
  {
    reel1->HomeReel();
    reel2->HomeReel();
    reel3->HomeReel();
    initialise_reel = false;

    reels_running = true;
  }
  if (!reels_running)
  {
    delay(500);
    reel1->DisableReel();
    reel2->DisableReel();
    reel3->DisableReel();
  }


  if (Serial.available())
  {
    char inChar = (char)Serial.read();
    if (inChar == 'S')
    {
      random_number1 = random(16);
      random_number2 = random(16);
      random_number3 = random(16);

      int end_pos1 = random_number1 * (degrees_per_sign / degrees_per_step);
      int end_pos2 = random_number2 * (degrees_per_sign / degrees_per_step);
      int end_pos3 = random_number3 * (degrees_per_sign / degrees_per_step);

      Serial.print("end_pos1: "); Serial.print(end_pos1); Serial.print(" | end_pos2: "); Serial.print(end_pos2); Serial.print(" | end_pos3: "); Serial.println(end_pos3);

      reel1->MoveTo(end_pos1);
      reel2->MoveTo(end_pos2);
      reel3->MoveTo(end_pos3);

      String tmp_string1 = reel1_signs[random_number1].info;
      String tmp_string2 = reel2_signs[random_number2].info;
      String tmp_string3 = reel3_signs[random_number3].info;

      Serial.print("Sign 1: "); Serial.println(tmp_string1);
      Serial.print("Sign 2: "); Serial.println(tmp_string2);
      Serial.print("Sign 3: "); Serial.println(tmp_string3);

      reel1->EnableReel();
      reel2->EnableReel();
      reel3->EnableReel();
    }
    else
    {
      Serial.println("Wrong input, type 'S' to start a new sequence");
    }
  }

  bool reel1_running = reel1->Run();
  bool reel2_running = reel2->Run();
  bool reel3_running = reel3->Run();

  if (reel1_running || reel2_running || reel3_running)
  {
    reels_running =  true;

  }
  else
  {
    reels_running = false;
  }
}


void SignConstructor()
{
  /*****************
        Reel 1:
   *****************/

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
  reel1_signs[9].position = 202.5;
  reel1_signs[9].info =     "questionmark 2";

  reel1_signs[10].symbol =   grape;
  reel1_signs[10].position = 225;
  reel1_signs[10].info =     "grape 3";

  reel1_signs[11].symbol =   questionmark;
  reel1_signs[11].position = 247.5;
  reel1_signs[11].info =     "questionmark 3";

  reel1_signs[12].symbol =   grape;
  reel1_signs[12].position = 270;
  reel1_signs[12].info =     "grape 4";

  reel1_signs[13].symbol =   berries;
  reel1_signs[13].position = 292.5;
  reel1_signs[13].info =     "berries 1";

  reel1_signs[14].symbol =   xtra;
  reel1_signs[14].position = 315;
  reel1_signs[14].info =     "xtra 1";

  reel1_signs[15].symbol =   pear;
  reel1_signs[15].position = 337.5;
  reel1_signs[15].info =     "pear 1";

  /*****************
       Reel 2:
  *****************/

  reel2_signs[0].symbol =   blue_x;
  reel2_signs[0].position = 0.0;
  reel2_signs[0].info =     "blue x 1";

  reel2_signs[1].symbol =   red_x;
  reel2_signs[1].position = 22.5;
  reel2_signs[1].info =     "red x 1";

  reel2_signs[2].symbol =   questionmark;
  reel2_signs[2].position = 45.0;
  reel2_signs[2].info =     "questionmark 1";

  reel2_signs[3].symbol =   grape;
  reel2_signs[3].position = 67.5;
  reel2_signs[3].info =     "grape 1";

  reel2_signs[4].symbol =   blue_x;
  reel2_signs[4].position = 90.0;
  reel2_signs[4].info =     "blue x 2";

  reel2_signs[5].symbol =   grape;
  reel2_signs[5].position = 112.5;
  reel2_signs[5].info =     "grape 2";

  reel2_signs[6].symbol =   questionmark;
  reel2_signs[6].position = 135.0;
  reel2_signs[6].info =     "questionmark 2";

  reel2_signs[7].symbol =   red_x;
  reel2_signs[7].position = 157.5;
  reel2_signs[7].info =     "red x 2";

  reel2_signs[8].symbol =   melon;
  reel2_signs[8].position = 180;
  reel2_signs[8].info =     "melon 1";

  reel2_signs[9].symbol =   berries;
  reel2_signs[9].position = 202.5;
  reel2_signs[9].info =     "berries 1";

  reel2_signs[10].symbol =   questionmark;
  reel2_signs[10].position = 225;
  reel2_signs[10].info =     "questionmark 3";

  reel2_signs[11].symbol =   pear;
  reel2_signs[11].position = 247.5;
  reel2_signs[11].info =     "pear 1";

  reel2_signs[12].symbol =   blue_x;
  reel2_signs[12].position = 270;
  reel2_signs[12].info =     "blue x 3";

  reel2_signs[13].symbol =   pear;
  reel2_signs[13].position = 292.5;
  reel2_signs[13].info =     "pear 2";

  reel2_signs[14].symbol =   xtra;
  reel2_signs[14].position = 315;
  reel2_signs[14].info =     "xtra 1";

  reel2_signs[15].symbol =   questionmark;
  reel2_signs[15].position = 337.5;
  reel2_signs[15].info =     "questionmark 4";

  /*****************
       Reel 3:
  *****************/

  reel3_signs[0].symbol =   grape;
  reel3_signs[0].position = 0.0;
  reel3_signs[0].info =     "grape 1";

  reel3_signs[1].symbol =   questionmark;
  reel3_signs[1].position = 22.5;
  reel3_signs[1].info =     "questionmark 1";

  reel3_signs[2].symbol =   grape;
  reel3_signs[2].position = 45.0;
  reel3_signs[2].info =     "grape 2";

  reel3_signs[3].symbol =   blue_x;
  reel3_signs[3].position = 67.5;
  reel3_signs[3].info =     "blue x 1";

  reel3_signs[4].symbol =   melon;
  reel3_signs[4].position = 90.0;
  reel3_signs[4].info =     "melon 1";

  reel3_signs[5].symbol =   blue_x;
  reel3_signs[5].position = 112.5;
  reel3_signs[5].info =     "blue x 2";

  reel3_signs[6].symbol =   pear;
  reel3_signs[6].position = 135.0;
  reel3_signs[6].info =     "pear 1";

  reel3_signs[7].symbol =   melon;
  reel3_signs[7].position = 157.5;
  reel3_signs[7].info =     "melon 2";

  reel3_signs[8].symbol =   pear;
  reel3_signs[8].position = 180;
  reel3_signs[8].info =     "pear 2";

  reel3_signs[9].symbol =   red_x;
  reel3_signs[9].position = 202.5;
  reel3_signs[9].info =     "red x 1";

  reel3_signs[10].symbol =   questionmark;
  reel3_signs[10].position = 225;
  reel3_signs[10].info =     "questionmark 2";

  reel3_signs[11].symbol =   red_x;
  reel3_signs[11].position = 247.5;
  reel3_signs[11].info =     "red x 2";

  reel3_signs[12].symbol =   xtra;
  reel3_signs[12].position = 270;
  reel3_signs[12].info =     "xtra 1";

  reel3_signs[13].symbol =   berries;
  reel3_signs[13].position = 292.5;
  reel3_signs[13].info =     "berries 1";

  reel3_signs[14].symbol =   grape;
  reel3_signs[14].position = 315;
  reel3_signs[14].info =     "grape 2";

  reel3_signs[15].symbol =   questionmark;
  reel3_signs[15].position = 337.5;
  reel3_signs[15].info =     "questionmark 3";
}
