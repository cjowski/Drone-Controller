#ifndef MOTOR_SPEED_H
#define MOTOR_SPEED_H

  #include <stdint.h>

  class MotorSpeed
  {
    public:
    enum UpdateType
    {
      Change,
      UsePrevious
    };
    UpdateType Type;
    uint32_t Value;

    MotorSpeed(UpdateType type, uint32_t value);
    MotorSpeed(UpdateType type);
  };

#endif