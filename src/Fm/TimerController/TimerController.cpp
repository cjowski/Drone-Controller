#include "TimerController.h"

void TimerController::SetupChannel(int channelNo)
{
  SetupChannel(channelNo);
}

void TimerController::Resume()
{
  Timer->resume();
}

void TimerController::Refresh()
{
  Timer->refresh();
}

int32_t TimerController::GetChannelValue(int channelNo)
{
  if (Channels[channelNo - 1].Initialized)
  {
    return Channels[channelNo - 1].OutputValue;
  }
  return -1;
}