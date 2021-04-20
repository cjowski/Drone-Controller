#ifndef MOTOR_MODE_H
#define MOTOR_MODE_H

  #include "Motor/MotorSpeed.h"

  class MotorMode
  {
    public:
    virtual MotorSpeed GetMotorSpeed() = 0;
  };

#endif
