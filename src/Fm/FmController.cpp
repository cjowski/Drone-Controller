#include "FmController.h"

FmController::FmController()
{
  MyTimerController = new Timer2(&HardwareTimer2);
  MyTimerController->Setup();
  MyTimerController->SetupChannel(1);
  MyTimerController->SetupChannel(2);
  MyTimerController->SetupChannel(3);
  MyTimerController->SetupChannel(4);
  MyTimerController->Resume();

  FmChannel *channels = new FmChannel[FM_CHANNELS_COUNT];
  for (int i = 0; i < FM_CHANNELS_COUNT; i++) {
    channels[i].AttachUpdateValueCallback(
      [&, i, channels] () {
        channels[i].TrySetNewValue(
          MyTimerController->GetChannelValue(i + 1)
        );
      }
    );
  }
  MyFmChannelsContainer = new FmChannelsContainer(channels, FM_CHANNELS_COUNT);
}

FmChannelsSerialValue* FmController::GetSerialValue()
{
  return MyFmChannelsContainer->GetSerialValue();
}

void FmController::Loop()
{
  MyFmChannelsContainer->UpdateChannelsValues();
}