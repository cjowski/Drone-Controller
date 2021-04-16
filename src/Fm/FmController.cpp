#include "FmController.h"

FmController::FmController()
{
  MyFmTimerController = new FmTimer2(&HardwareTimer2);
  MyFmTimerController->Setup();
  MyFmTimerController->SetupChannel(1);
  MyFmTimerController->SetupChannel(2);
  MyFmTimerController->SetupChannel(3);
  MyFmTimerController->SetupChannel(4);
  MyFmTimerController->Resume();

  FmChannel *channels = new FmChannel[FM_CHANNELS_COUNT];
  for (int i = 0; i < FM_CHANNELS_COUNT; i++) {
    channels[i].AttachUpdateValueCallback(
      [&, i, channels] () {
        channels[i].TrySetNewValue(
          MyFmTimerController->GetChannelValue(i + 1)
        );
      }
    );
  }
  MyFmChannelsContainer = new FmChannelsContainer(channels, FM_CHANNELS_COUNT);
}

FmChannel::SignalState FmController::GetFmSignalState()
{
  return MyFmChannelsContainer->GetFmSignalState();
}

int32_t FmController::GetFmChannelValue(int channelNo)
{
  return MyFmChannelsContainer->GetFmChannelValue(channelNo);
}

FmChannelsSerialValue* FmController::GetSerialValue()
{
  return MyFmChannelsContainer->GetSerialValue();
}

void FmController::Loop()
{
  MyFmChannelsContainer->UpdateChannelsValues();
}