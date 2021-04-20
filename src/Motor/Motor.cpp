#include "Motor.h"

Motor::Motor(
  MotorTimerChannel *timerChannel,
  MotorMode *mode
)
{
  TimerChannel = timerChannel;
  Mode = mode;
}

uint32_t Motor::GetSpeed()
{
  MotorSpeed speed = Mode->GetMotorSpeed();

  if (speed.Type == MotorSpeed::UsePrevious)
  {
    return PreviousSpeed;
  }

  if (speed.Value < MotorTimerController::MIN_PWM_VALUE)
  {
    return MotorTimerController::MIN_PWM_VALUE;
  }

  if (speed.Value > MotorTimerController::MAX_PWM_VALUE)
  {
    return MotorTimerController::MAX_PWM_VALUE;
  }

  return speed.Value;
}

void Motor::Loop()
{
  uint32_t currentSpeed = GetSpeed();
  TimerChannel->SetValue(currentSpeed);
  PreviousSpeed = currentSpeed;

  long currentTime = millis();
  if (currentTime - PreviousPrintTime > 500)
  {
    Serial.println(currentSpeed);
    PreviousPrintTime = currentTime;
  }
}