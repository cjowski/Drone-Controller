#include "MotorTimerChannel.h"

MotorTimerChannel::MotorTimerChannel(
  int channelNo,
  int timerNo,
  HardwareTimer *timer,
  TIM_TypeDef *timerBase
)
{
  ChannelNo = channelNo;
  TimerNo = timerNo;
  Timer = timer;
  TimerBase = timerBase;
}

void MotorTimerChannel::SetValue(uint32_t value)
{
  SetCaptureCompareRegisterValue(value);
}

int MotorTimerChannel::GetTimerNo()
{
  return TimerNo;
}

HardwareTimer *MotorTimerChannel::GetTimer()
{
  return Timer;
}

void MotorTimerChannel::SetCaptureCompareRegisterValue(
  uint32_t value
)
{
  switch (ChannelNo)
  {
    case 1:
      TimerBase->CCR1 = value;
      break;
    case 2:
      TimerBase->CCR2 = value;
      break;
    case 3:
      TimerBase->CCR3 = value;
      break;
    case 4:
      TimerBase->CCR4 = value;
      break;
    default:
      return;
  }
}