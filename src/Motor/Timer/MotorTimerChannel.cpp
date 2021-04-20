#include "MotorTimerChannel.h"

MotorTimerChannel::MotorTimerChannel(
  int channelNo,
  MotorTimerController *timerController
)
{
  ChannelNo = channelNo;
  TimerController = timerController;
}

void MotorTimerChannel::SetValue(uint32_t value)
{
  TimerController->SetChannelValue(
    ChannelNo,
    value
  );
}