#include "Reel.hpp"

Reel* Reel::this_reel = 0;

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
  interrupt_fired = false;

  init_enable = false;
  init_home = true;
  init_disable = true;

  pinMode(wire_1_pin, OUTPUT);
  pinMode(wire_2_pin, OUTPUT);
  pinMode(wire_3_pin, OUTPUT);
  pinMode(wire_4_pin, OUTPUT);
  pinMode(light_sensor_pin, INPUT);
  
  reel_stepper = new AccelStepper(AccelStepper::HALF4WIRE, wire_1_pin, wire_2_pin, wire_3_pin, wire_4_pin, true);

  reel_stepper->setMaxSpeed(max_speed);            //steps per second            [steps / s]
  reel_stepper->setAcceleration(max_acceleration); //steps per second per second [steps / s^2]

  this_reel = this;
  attachInterrupt(digitalPinToInterrupt(light_sensor_pin), Reel::LightGateInterrupt, FALLING);
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
        reel_stepper->stop();
        reel_stepper->disableOutputs();
      }
      
      delay(10);
      
      break;

    case initialise:
      if (init_home)
      {
        InitHomingState();

        reel_stepper->setSpeed(min_speed); 

      }
      if(interrupt_fired || ReelAtHomePosition())
      {
        reel_stepper->stop();
        interrupt_fired = false;
        reel_stepper->setCurrentPosition(0);
        DisableReel();
        return false;
      }

      reel_stepper->runSpeed();
      return true;
      
      break;

    case enable:
      if (init_enable)
      {
        InitEnableState();
      }

      reel_stepper->run();
      reel_running = StepsToGo() != 0;
       
      break;      
  }
  return reel_running;
}


void Reel::MoveTo(int reel_position)
{
  reel_stepper->moveTo(reel_position);
}

int Reel::StepsToGo()
{
  return reel_stepper->distanceToGo();
}


bool Reel::ReelAtHomePosition()
{
  return !digitalRead(light_sensor_pin);
}


void Reel::LightGateInterruptHandler()
{
  interrupt_fired = true;
}


void Reel::LightGateInterrupt()
{
  if(this_reel != 0)
  {
    this_reel->LightGateInterruptHandler();
  }  
}


void Reel::InitEnableState()
{
  init_enable = false;
  init_home = true;
  init_disable = true;
}


void Reel::InitHomingState()
{
  init_enable = true;
  init_home = false;  
  init_disable = true;
}


void Reel::InitDisableState()
{
  init_enable = true;
  init_home = true;
  init_disable = false;  
}


void Reel::EnableReel()
{
  operatingState = enable;
}


void Reel::HomeReel()
{
  operatingState = initialise;
}


void Reel::DisableReel()
{
  operatingState = disable;
}
