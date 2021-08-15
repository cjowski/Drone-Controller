#include "FmTimerChannel.h"

FmTimerChannel::FmTimerChannel(
  int channelNo,
  int timerNo,
  int channelPin,
  HardwareTimer *timer
)
{
  ChannelNo = channelNo;
  TimerNo = timerNo;
  ChannelPin = channelPin;
  Timer = timer;
}

void FmTimerChannel::InterruptHandler(
  uint8_t channelPin,
  int32_t *outputValue,
  int32_t *startValue,
  volatile uint32_t *captureCompareReg,
  volatile uint32_t *captureCompareEnableReg,
  unsigned long captureCompareOutPolarity
)
{
  if (digitalRead(channelPin) == HIGH)
  {
    *startValue = *captureCompareReg;
    *captureCompareEnableReg |= captureCompareOutPolarity;
  }
  else
  {
    *outputValue = *captureCompareReg - *startValue;
    if (*outputValue < 0)
    {
      *outputValue += 0xFFFF;
    }
    *captureCompareEnableReg &= ~captureCompareOutPolarity;
  }
}

void FmTimerChannel::Setup(
  BoardTimerChannelSetup *channelSetup
)
{
  pinMode(ChannelPin, INPUT);

  Timer->setMode(
    ChannelNo,
    TIMER_INPUT_CAPTURE_RISING,
    ChannelPin
  );
  
  Timer->attachInterrupt(
    ChannelNo,
    [=] () {
      InterruptHandler(
        ChannelPin,
        &(OutputValue),
        &(StartValue),
        GetCaptureCompareRegister(channelSetup->GetTimerBase()),
        &(channelSetup->GetTimerBase())->CCER,
        GetCaptureCompareOutPolarity()
      );
    }
  );
}

volatile uint32_t* FmTimerChannel::GetCaptureCompareRegister(
  TIM_TypeDef *timerBase
)
{
  switch (ChannelNo)
  {
    case 1:
      return &(timerBase)->CCR1;
    case 2:
      return &(timerBase)->CCR2;
    case 3:
      return &(timerBase)->CCR3;
    case 4:
      return &(timerBase)->CCR4;
    default:
      return &(timerBase)->CCR1; //more channels not supported
  }
}

unsigned long FmTimerChannel::GetCaptureCompareOutPolarity()
{
  switch (ChannelNo)
  {
    case 1:
      return TIM_CCER_CC1P;
    case 2:
      return TIM_CCER_CC2P;
    case 3:
      return TIM_CCER_CC3P;
    case 4:
      return TIM_CCER_CC4P;
    default:
      return -1; //more channels not supported
  }
}

int FmTimerChannel::GetChannelNo()
{
  return ChannelNo;
}

int FmTimerChannel::GetTimerNo()
{
  return TimerNo;
}

HardwareTimer *FmTimerChannel::GetTimer()
{
  return Timer;
}

int32_t FmTimerChannel::GetOutputValue()
{
  return OutputValue;
}