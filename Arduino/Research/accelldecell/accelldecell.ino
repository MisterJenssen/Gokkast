#include "ReelConfig.hpp"
#include "OperatingState.hpp"
#include "Reel.hpp"

#define baudrate  9600

Reel *reel1;
Reel *reel2;

int end_pos1 = -1000;
int end_pos2 = 1000;

//void lightGateInterrupt();

void setup()
{  
  Serial.begin(baudrate);

  reel1 = new Reel(reel_1_wire_1_pin, reel_1_wire_2_pin, reel_1_wire_3_pin, reel_1_wire_4_pin, reel_1_light_sensor_pin, reel_1_min_speed, reel_1_max_speed, reel_1_min_acceleration, reel_1_max_acceleration);
  reel2 = new Reel(reel_2_wire_1_pin, reel_2_wire_2_pin, reel_2_wire_3_pin, reel_2_wire_4_pin, reel_2_light_sensor_pin, reel_2_min_speed, reel_2_max_speed, reel_2_min_acceleration, reel_2_max_acceleration);

  reel1->MoveTo(end_pos1);
  reel2->MoveTo(end_pos2);

  reel1->EnableReel();
  reel2->EnableReel();
}

void loop()
{
   bool reel1_running = reel1->Run();
   bool reel2_running = reel2->Run();
   if(reel1->StepsToGo() == 0)
   {
      end_pos1 =  -end_pos1;
      reel1->MoveTo(end_pos1);   
   }
   if(reel2->StepsToGo() == 0)
   {
      end_pos2 =  -end_pos2;
      reel2->MoveTo(end_pos2);   
   }

    if (Serial.available()) 
    {
      char inChar = (char)Serial.read();
      if(inChar=='S') 
      {
        reel1->DisableReel();
        reel2->DisableReel();

        Serial.println("Reels stopped");
        while(true);
      }
    }   
}

/*
void lightGateInterrupt()
{
    int value = digitalRead(light_gate_pin);
    Serial.print("Value: ");
    Serial.println(value);
}
*/
