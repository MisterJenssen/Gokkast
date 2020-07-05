#ifndef REEL_H
#define REEL_H

#include <AccelStepper.h>

//Enum used to define the movement state of the reel
#include "OperatingState.hpp"

class Reel
{
  private:
    int wire_1_pin;
    int wire_2_pin;
    int wire_3_pin;
    int wire_4_pin;
    int light_sensor_pin;
    int min_speed;
    int max_speed;
    int min_acceleration;
    int max_acceleration;
    
    AccelStepper *reel_stepper;
    OperatingState operatingState;
    
    bool reel_running;
    bool init_enable;
    bool init_halt;
    bool init_disable;
    
    void InitEnableState();
    void InitHaltState();
    void InitDisableState();

  public:
    Reel(int wire_1_pin, int wire_2_pin, int wire_3_pin, int wire_4_pin, int light_sensor_pin, int min_speed, int max_speed, int min_acceleration, int max_acceleration);
    virtual ~Reel();
    bool Run();
    void MoveTo(int reel_position);
    void EnableReel();
    void HaltReel();
    void DisableReel();
};

#endif /* REEL_H */
