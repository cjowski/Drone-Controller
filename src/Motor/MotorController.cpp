#include "MotorController.h"

MotorController::MotorController(MotorMode *motorMode)
{
  TimerController = new MotorTimer1();
  TimerController->Setup();
  for (int i = 0; i < MOTORS_COUNT; i++)
  {
    TimerController->SetupChannel(i + 1);
    Motors[i] = new Motor(
      new MotorTimerChannel(i + 1, TimerController),
      motorMode
    );
  }
}

void MotorController::Loop()
{
  for (int i = 0; i < MOTORS_COUNT; i++)
  {
    Motors[i]->Loop();
  }
  TimerController->Resume();
}