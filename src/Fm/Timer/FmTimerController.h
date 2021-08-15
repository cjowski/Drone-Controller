#ifndef FM_TIMER_CONTROLLER_H
#define FM_TIMER_CONTROLLER_H

  #include <map>
  #include "FmTimerChannel.h"
  
  class FmTimerController
  {
    private:
    const BoardTimerSetup *FmBoardTimerSetup;
    std::list<FmTimerChannel*> Channels;
    const int MAX_CHANNELS_COUNT = 4;

    public:
    FmTimerController(const BoardTimerSetup *fmBoardTimerSetup);
    void Setup();
    void Resume();
    void Refresh();
    int32_t GetChannelValue(int channelIndex);

    private:
    void SetupTimer(TIM_TypeDef* timerBase);
    void SetupChannel(
      BoardTimerChannelSetup *channelSetup,
      HardwareTimer *timer
    );
    std::list<HardwareTimer*> GetTimers();
  };

#endif