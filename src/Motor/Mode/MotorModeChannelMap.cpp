#include "MotorModeChannelMap.h"

MotorModeChannelMap::MotorModeChannelMap(
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

uint32_t MotorModeChannelMap::MapFmChannelValueToSpeed(int fmChannelValue)
{
  if (fmChannelValue < MinChannelValue)
  {
    return MIN_MAP_VALUE;
  }

  if (fmChannelValue > MaxChannelValue)
  {
    return MAX_MAP_VALUE;
  }

  return (fmChannelValue - MinChannelValue)
    * (MAX_MAP_VALUE - MIN_MAP_VALUE)
    / (MaxChannelValue - MinChannelValue)
    + MIN_MAP_VALUE;
}

MotorSpeed MotorModeChannelMap::GetMotorSpeed()
{
  if (!IsFmSignalActive())
  {
    return MotorSpeed(
      MotorSpeed::UsePrevious
    );
  }

  return MotorSpeed(
    MotorSpeed::Change,
    MapFmChannelValueToSpeed(
      GetFmChannelValue()
    )
  );
}