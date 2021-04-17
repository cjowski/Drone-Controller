#include "FmTimerChannel.h"

FmTimerChannel::FmTimerChannel(
  int channelNo,
  int channelPin,
  HardwareTimer *timer
)
{
  ChannelNo = channelNo;
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
  volatile uint32_t *captureCompareReg,
  volatile uint32_t *captureCompareEnableReg,
  unsigned long captureCompareOutPolarity
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
        captureCompareReg,
        captureCompareEnableReg,
        captureCompareOutPolarity
      );
    }
  );
}

int FmTimerChannel::GetChannelNo()
{
  return ChannelNo;
}

int32_t FmTimerChannel::GetOutputValue()
{
  return OutputValue;
}