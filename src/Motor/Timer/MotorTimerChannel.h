#ifndef MOTOR_TIMER_CHANNEL_H
#define MOTOR_TIMER_CHANNEL_H

  #include "Board/BoardTimer/BoardTimerSetup.h"

  class MotorTimerChannel
  {
    private:
    int ChannelNo;
    int TimerNo;
    HardwareTimer *Timer;
    TIM_TypeDef *TimerBase;

    public:
    MotorTimerChannel(
      int channelNo,
      int timerNo,
      HardwareTimer *timer,
      TIM_TypeDef *timerBase
    );
    void SetValue(uint32_t value);
    int GetTimerNo();
    HardwareTimer *GetTimer();

    private:
    void SetCaptureCompareRegisterValue(uint32_t value);
  };

#endif