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

SerialEncoderInput *MotorController::GetSerialEncoderInput()
{
  std::list<String> texts;
  texts.push_back(String((long)millis()));
  for (int i = 0; i < MOTORS_COUNT; i++)
  {
    texts.push_back(String(Motors[i]->GetPreviousSpeed()));
  }

  return new StringListEncoderInput(
    SERIAL_KEY,
    texts
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