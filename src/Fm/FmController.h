#ifndef FM_CONTROLLER_H
#define FM_CONTROLLER_H

  #include "Fm/TimerController/FmTimer2.h"
  #include "Fm/FmChannels/FmChannelsContainer.h"
  #include "Fm/FmChannels/FmChannelsSerialValue.h"

  class FmController
  {
    public:
    FmController();
    FmChannel::SignalState GetFmSignalState();
    int32_t GetFmChannelValue(int channelNo);
    FmChannelsSerialValue *GetSerialValue();
    void Loop();

    private:
    const int FM_CHANNELS_COUNT = 4;
    HardwareTimer HardwareTimer2 = HardwareTimer(TIM2);
    FmTimerController *MyFmTimerController;
    FmChannelsContainer *MyFmChannelsContainer;
  };

#endif