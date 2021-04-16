#include "FmTimerController.h"

void FmTimerController::SetupChannel(int channelNo)
{
  SetupChannel(channelNo);
}

void FmTimerController::Resume()
{
  Timer->resume();
}

void FmTimerController::Refresh()
{
  Timer->refresh();
}

int32_t FmTimerController::GetChannelValue(int channelNo)
{
  if (Channels[channelNo - 1].Initialized)
  {
    return Channels[channelNo - 1].OutputValue;
  }
  return -1;
}