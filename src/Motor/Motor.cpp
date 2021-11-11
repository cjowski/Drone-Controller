#include "Motor.h"

Motor::Motor(
  MotorMode *mode,
  std::function<void(uint32_t)> setChannelValue,
  uint32_t minSpeed,
  uint32_t maxSpeed
)
{
  Mode = mode;
  SetChannelValue = setChannelValue;
  MinSpeed = minSpeed;
  MaxSpeed = maxSpeed;
}

uint32_t Motor::GetSpeed()
{
  MotorSpeed speed = Mode->GetMotorSpeed();

  if (speed.Type == MotorSpeed::UsePrevious)
  {
    return PreviousSpeed;
  }

  if (speed.Value < MinSpeed)
  {
    return MinSpeed;
  }

  if (speed.Value > MaxSpeed)
  {
    return MaxSpeed;
  }

  return speed.Value;
}

uint32_t Motor::GetPreviousSpeed()
{
  return PreviousSpeed;
}

void Motor::Loop()
{
  uint32_t currentSpeed = GetSpeed();
  SetChannelValue(currentSpeed);
  PreviousSpeed = currentSpeed;
}