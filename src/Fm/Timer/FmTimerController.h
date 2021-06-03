#ifndef FM_TIMER_CONTROLLER_H
#define FM_TIMER_CONTROLLER_H

  #include <list>
  #include "FmTimerChannel.h"
  #include "Board/BoardTimer.h"
  
  class FmTimerController
  {
    private:
    HardwareTimer *Timer;
    const BoardTimer *FmBoardTimer;
    std::list<FmTimerChannel*> Channels;
    const int MAX_CHANNELS_COUNT = 4;

    public:
    FmTimerController(const BoardTimer *boardTimer);
    void Setup();
    void SetupChannel(int channelNo);
    void Resume();
    void Refresh();
    int32_t GetChannelValue(int channelNo);
  };

#endif