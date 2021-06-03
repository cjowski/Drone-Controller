#ifndef FM_CONTROLLER_H
#define FM_CONTROLLER_H

  #include "Fm/Timer/FmTimerController.h"
  #include "Fm/FmChannels/FmChannelsContainer.h"
  #include "Fm/FmChannels/FmChannelsSerialValue.h"

  class FmController
  {
    public:
    FmController(const BoardTimer *boardTimer);
    FmChannel::SignalState GetFmSignalState();
    int32_t GetFmChannelValue(int channelNo);
    FmChannelsSerialValue *GetSerialValue();
    void Loop();

    private:
    const int FM_CHANNELS_COUNT = 4;
    FmTimerController *MyFmTimerController;
    FmChannelsContainer *MyFmChannelsContainer;
  };

#endif