#ifndef MOTOR_H
#define MOTOR_H

  #include <functional>
  #include "Mode/MotorMode.h"

  class Motor
  {
    private:
    MotorMode *Mode;
    uint32_t PreviousSpeed;
    uint32_t GetSpeed();
    std::function<void(uint32_t)> SetChannelValue;
    uint32_t MinSpeed;
    uint32_t MaxSpeed;

    public:
    Motor(
      MotorMode *mode,
      std::function<void(uint32_t)> setChannelValue,
      uint32_t minSpeed,
      uint32_t maxSpeed
    );
    uint32_t GetPreviousSpeed();
    void Loop();
  };

#endif