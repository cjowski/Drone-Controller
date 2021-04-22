#ifndef MOTOR_H
#define MOTOR_H

  #include "Timer/MotorTimerChannel.h"
  #include "Mode/MotorMode.h"

  #define PWM_PIN PA6

  class Motor
  {
    private:
    MotorTimerChannel *TimerChannel;
    MotorMode *Mode;
    uint32_t PreviousSpeed = MotorTimerController::MIN_PWM_VALUE;
    uint32_t GetSpeed();
    long PreviousPrintTime = 0;

    public:
    Motor(
      MotorTimerChannel *timerChannel,
      MotorMode *mode
    );
    uint32_t GetPreviousSpeed();
    void Loop();
  };

#endif