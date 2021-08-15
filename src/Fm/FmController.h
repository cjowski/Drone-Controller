#ifndef FM_CONTROLLER_H
#define FM_CONTROLLER_H

  #include "Fm/Timer/FmTimerController.h"
  #include "Fm/FmChannels/FmChannelsContainer.h"

  class FmController
  {
    public:
    FmController(const BoardTimerSetup *fmBoardTimerSetup);
    FmChannel::SignalState GetFmSignalState();
    int32_t GetFmChannelValue(int channelIndex);
    SerialEncoderInput *GetSerialEncoderInput();
    void Setup();
    void Loop();

    private:
    FmTimerController *MyFmTimerController;
    FmChannelsContainer *MyFmChannelsContainer;
  };

#endif