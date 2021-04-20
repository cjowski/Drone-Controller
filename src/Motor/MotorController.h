#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

  #include "Motor.h"
  #include "Timer/MotorTimer1.h"

  class MotorController
  {
    private:
    static const int MOTORS_COUNT = 4;
    Motor *Motors[MOTORS_COUNT];
    MotorTimerController *TimerController;

    public:
    MotorController(MotorMode *motorMode);
    void Loop();
  };

#endif