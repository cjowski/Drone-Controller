#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

  #include "Motor.h"
  #include "Timer/MotorTimerController.h"
  #include <Serial/Type/StringList/Encoder/StringListEncoderInput.h>

  class MotorController
  {
    private:
    static const int MOTORS_COUNT = 4;
    Motor *Motors[MOTORS_COUNT];
    MotorTimerController *TimerController;
    char SERIAL_KEY = 'M';

    public:
    MotorController(
      MotorMode *motorMode,
      const BoardTimerSetup *motorBoardTimerSetup
    );
    SerialEncoderInput *GetSerialEncoderInput();
    void Setup();
    void Loop();
  };

#endif