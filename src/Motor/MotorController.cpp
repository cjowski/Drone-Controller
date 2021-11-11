#include "MotorController.h"

MotorController::MotorController(
  MotorMode *motorMode,
  const BoardTimerSetup *motorBoardTimerSetup
)
{
  TimerController = new MotorTimerController(motorBoardTimerSetup);
  for (int i = 0; i < MOTORS_COUNT; i++)
  {
    Motors[i] = new Motor(
      motorMode,
      [=] (uint32_t value) {
        TimerController->SetChannelValue(i + 1, value);
      },
      MotorTimerController::MIN_PWM_VALUE,
      MotorTimerController::MAX_PWM_VALUE
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

void MotorController::Setup()
{
  TimerController->Setup();
}

void MotorController::Loop()
{
  for (int i = 0; i < MOTORS_COUNT; i++)
  {
    Motors[i]->Loop();
  }
  TimerController->Resume();
}