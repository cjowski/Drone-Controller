#ifndef TIMER_CONTROLLER_H
#define TIMER_CONTROLLER_H

  #include "TimerChannel.h"
  
  class TimerController
  {
    public:
    TimerController() { };
    TimerController(HardwareTimer *timer) { };
    virtual void Setup() = 0;
    virtual void SetupChannel(int channelNo);
    void Resume();
    void Refresh();
    int32_t GetChannelValue(int channelNo);

    protected:
    HardwareTimer *Timer;
    TimerChannel *Channels;
  };

#endif