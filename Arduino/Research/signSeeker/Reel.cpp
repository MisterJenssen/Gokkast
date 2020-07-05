#include "Reel.hpp"

Reel::Reel(int wire_1_pin, int wire_2_pin, int wire_3_pin, int wire_4_pin, int light_sensor_pin, int min_speed, int max_speed, int min_acceleration, int max_acceleration)
            : wire_1_pin(wire_1_pin)
            , wire_2_pin(wire_2_pin)
            , wire_3_pin(wire_3_pin)
            , wire_4_pin(wire_4_pin)
            , light_sensor_pin(light_sensor_pin)
            , min_speed(min_speed)
            , max_speed(max_speed)
            , min_acceleration(min_acceleration)
            , max_acceleration(max_acceleration)
{
  operatingState = disable;
  reel_running = false;

  init_enable = false;
  init_halt = false;
  init_disable = true;

  pinMode(wire_1_pin, OUTPUT);
  pinMode(wire_2_pin, OUTPUT);
  pinMode(wire_3_pin, OUTPUT);
  pinMode(wire_4_pin, OUTPUT);
  pinMode(light_sensor_pin, INPUT);
  
  reel_stepper = new AccelStepper(AccelStepper::HALF4WIRE, wire_1_pin, wire_2_pin, wire_3_pin, wire_4_pin, true);

  reel_stepper->setMaxSpeed(max_speed);            //steps per second            [steps / s]
  reel_stepper->setAcceleration(max_acceleration); //steps per second per second [steps / s^2]
}


Reel::~Reel()
{
  if(reel_stepper != NULL)
  {
    reel_stepper->stop();
    delete reel_stepper;
    reel_stepper = NULL; 
  }  
}


bool Reel::Run()
{
  switch (operatingState)
  {
    case disable:
      if (init_disable)
      {
        InitDisableState();
      }
      
      delay(10);
      
      break;

    case halt:
      if (init_halt)
      {
        InitHaltState();
      }

      delay(10);
      
      break;

    case enable:
      if (init_enable)
      {
        InitEnableState();
      }

      reel_running = reel_stepper->run();
       
      break;      
  }
  return reel_running;
}


void Reel::MoveTo(int reel_position)
{
  reel_stepper->moveTo(reel_position);
}


void Reel::InitEnableState()
{
  init_enable = false;
  init_halt = true;
  init_disable = true;
}


void Reel::InitHaltState()
{
  init_enable = true;
  init_halt = false;  
  init_disable = true;
}


void Reel::InitDisableState()
{
  init_enable = true;
  init_halt = true;
  init_disable = false;  
}


void Reel::EnableReel()
{
  operatingState = enable;
}


void Reel::HaltReel()
{
  operatingState = halt;
}


void Reel::DisableReel()
{
  operatingState = disable;
}
