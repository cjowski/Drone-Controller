#ifndef MOTOR_TIMER_CHANNEL_H
#define MOTOR_TIMER_CHANNEL_H

  #include "MotorTimerController.h"

  class MotorTimerChannel
  {
    private:
    int ChannelNo;
    MotorTimerController *TimerController;

    public:
    MotorTimerChannel(int channelNo, MotorTimerController *timerController);
    void SetValue(uint32_t value);
  };

#endif