#ifndef FM_TIMER_CONTROLLER_H
#define FM_TIMER_CONTROLLER_H

  #include <list>
  #include "FmTimerChannel.h"
  
  class FmTimerController
  {
    private:
    std::list<FmTimerChannel*> Channels;
    const int MAX_CHANNELS_COUNT = 4;

    protected:
    HardwareTimer *Timer;

    public:
    FmTimerController() { };
    virtual const uint8_t *CHANNEL_PINS() const = 0;
    virtual int CHANNELS_COUNT() const = 0;
    virtual TIM_TypeDef *TIMER_BASE() const = 0;
    void Setup();
    void SetupChannel(int channelNo);
    void Resume();
    void Refresh();
    int32_t GetChannelValue(int channelNo);
  };

#endif