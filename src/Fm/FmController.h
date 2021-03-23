#ifndef FM_CONTROLLER_H
#define FM_CONTROLLER_H

  #include "Fm/TimerController/Timer2.h"
  #include "Fm/FmChannels/FmChannelsContainer.h"

  class FmController
  {
    public:
    FmController();
    std::list<String> GetPrintStrings();
    void Loop();

    private:
    const int FM_CHANNELS_COUNT = 4;
    HardwareTimer HardwareTimer2 = HardwareTimer(TIM2);
    TimerController *MyTimerController;
    FmChannelsContainer *MyFmChannelsContainer;
  };

#endif