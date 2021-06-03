#include "MotorController.h"

MotorController::MotorController(
  MotorMode *motorMode,
  const BoardTimer *motorBoardTimer
)
{
  TimerController = new MotorTimerController(motorBoardTimer);
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

MotorsSerialValue *MotorController::GetSerialValue()
{
  return new MotorsSerialValue(
    (long)millis(),
    Motors[0]->GetPreviousSpeed(),
    Motors[1]->GetPreviousSpeed(),
    Motors[2]->GetPreviousSpeed(),
    Motors[3]->GetPreviousSpeed()
  );
}

void MotorController::Loop()
{
  for (int i = 0; i < MOTORS_COUNT; i++)
  {
    Motors[i]->Loop();
  }
  TimerController->Resume();
}