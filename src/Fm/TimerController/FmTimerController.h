#ifndef FM_TIMER_CONTROLLER_H
#define FM_TIMER_CONTROLLER_H

  #include "FmTimerChannel.h"
  
  class FmTimerController
  {
    public:
    FmTimerController() { };
    FmTimerController(HardwareTimer *timer) { };
    virtual void Setup() = 0;
    virtual void SetupChannel(int channelNo);
    void Resume();
    void Refresh();
    int32_t GetChannelValue(int channelNo);

    protected:
    HardwareTimer *Timer;
    FmTimerChannel *Channels;
  };

#endif