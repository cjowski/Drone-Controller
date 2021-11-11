#ifndef MOTOR_TIMER_CONTROLLER_H
#define MOTOR_TIMER_CONTROLLER_H

  #include <list>
  #include <map>
  #include <PinConfigured.h>
  #include "MotorTimerChannel.h"
  
  class MotorTimerController
  {
    private:
    const BoardTimerSetup *MotorBoardTimerSetup;
    std::list<MotorTimerChannel*> Channels;
    const int MAX_CHANNELS_COUNT = 4;

    public:
    static const uint32_t MAX_PWM_VALUE = 2000;
    static const uint32_t MIN_PWM_VALUE = 1000;
    MotorTimerController(const BoardTimerSetup *motorBoardTimerSetup);
    void Setup();
    void Resume();
    void Refresh();
    void SetChannelValue(int channelNo, uint32_t value);

    private:
    void SetupTimer(TIM_TypeDef* timerBase);
    void SetupChannel(
      BoardTimerChannelSetup *channelSetup,
      HardwareTimer *timer
    );
    MotorTimerChannel *GetChannel(int channelNo);
    std::list<HardwareTimer*> GetTimers();
  };

#endif