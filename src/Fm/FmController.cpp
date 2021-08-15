#include "FmController.h"

FmController::FmController(const BoardTimerSetup *fmBoardTimerSetup)
{
  MyFmTimerController = new FmTimerController(fmBoardTimerSetup);
  FmChannel *channels = new FmChannel[fmBoardTimerSetup->GetChannelsCount()];

  for (int i = 0; i < fmBoardTimerSetup->GetChannelsCount(); i++) {
    channels[i].AttachUpdateValueCallback(
      [&, i, channels] () {
        channels[i].TrySetNewValue(
          MyFmTimerController->GetChannelValue(i)
        );
      }
    );
  }

  MyFmChannelsContainer = new FmChannelsContainer(
    channels,
    fmBoardTimerSetup->GetChannelsCount()
  );
}

void FmController::Setup()
{
  MyFmTimerController->Setup();
  MyFmTimerController->Resume();
}

FmChannel::SignalState FmController::GetFmSignalState()
{
  return MyFmChannelsContainer->GetFmSignalState();
}

int32_t FmController::GetFmChannelValue(int channelIndex)
{
  return MyFmChannelsContainer->GetFmChannelValue(channelIndex);
}

SerialEncoderInput* FmController::GetSerialEncoderInput()
{
  return MyFmChannelsContainer->GetSerialEncoderInput();
}

void FmController::Loop()
{
  MyFmChannelsContainer->UpdateChannelsValues();
}