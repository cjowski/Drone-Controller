#include "Motor.h"

Motor::Motor(
  int minChannelValue,
  int maxChannelValue,
  std::function<bool(void)> isFmSignalActive,
  std::function<int(void)> getFmChannelValue
)
{
  MinChannelValue = minChannelValue;
  MaxChannelValue = maxChannelValue;
  IsFmSignalActive = isFmSignalActive;
  GetFmChannelValue = getFmChannelValue;
}

int Motor::GetSpeed()
{
  if (!IsFmSignalActive())
  {
    return PreviousSpeed;
  }

  return MapFmChannelValueToSpeed(
    GetFmChannelValue()
  );
}

int Motor::MapFmChannelValueToSpeed(int fmChannelValue)
{
  if (fmChannelValue < MinChannelValue)
  {
    return MIN_SPEED;
  }

  if (fmChannelValue > MaxChannelValue)
  {
    return MAX_SPEED;
  }

  return (fmChannelValue - MinChannelValue)
    * (MAX_SPEED - MIN_SPEED)
    / (MaxChannelValue - MinChannelValue)
    + MIN_SPEED;
}

void Motor::Loop()
{
  int currentSpeed = GetSpeed();
  // Serial.println(
  //   currentSpeed
  // );
  PreviousSpeed = currentSpeed;
}