#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

  #include "Motor.h"
  #include "MotorsSerialValue.h"

  class MotorController
  {
    private:
    static const int MOTORS_COUNT = 4;
    Motor *Motors[MOTORS_COUNT];
    MotorTimerController *TimerController;

    public:
    MotorController(
      MotorMode *motorMode,
      const BoardTimer *motorBoardTimer
    );
    MotorsSerialValue *GetSerialValue();
    void Loop();
  };

#endif