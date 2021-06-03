#ifndef MOTOR_TIMER_CONTROLLER_H
#define MOTOR_TIMER_CONTROLLER_H

  #include <list>
  #include <PinConfigured.h>
  #include "Board/BoardTimer.h"
  
  class MotorTimerController
  {
    private:
    HardwareTimer *Timer;
    const BoardTimer *MotorBoardTimer;
    std::list<int> ChannelNos;
    const int MAX_CHANNELS_COUNT = 4;

    public:
    static const uint32_t MAX_PWM_VALUE = 2000;
    static const uint32_t MIN_PWM_VALUE = 1000;
    MotorTimerController(const BoardTimer *boardTimer);
    void Setup();
    void SetupChannel(int channelNo);
    void Resume();
    void Refresh();
    void SetChannelValue(int channelNo, uint32_t value);
  };

#endif