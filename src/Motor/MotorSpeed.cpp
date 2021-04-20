#include "MotorSpeed.h"

MotorSpeed::MotorSpeed(
  UpdateType type,
  uint32_t value
)
{
  Type = type;
  Value = value;
}

MotorSpeed::MotorSpeed(
  UpdateType type
)
{
  Type = type;
  Value = -1;
}