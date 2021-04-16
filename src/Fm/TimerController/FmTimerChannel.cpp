#include "FmTimerChannel.h"

FmTimerChannel::FmTimerChannel(int channelNo, HardwareTimer *timer)
{
  Timer = timer;
  ChannelNo = channelNo;
  ChannelPin = -1;
  Initialized = false;
  StartValue = 0;
  OutputValue = 0;
}

void FmTimerChannel::Setup(
  uint8_t channelPin,
  TimerModes_t timerMode,
  volatile uint32_t *captureCompareReg,
  volatile uint32_t *captureCompareEnableReg,
  unsigned long captureCompareOutPolarity
)
{
  pinMode(channelPin, INPUT);
  Timer->setMode(ChannelNo, timerMode, channelPin);
  Timer->attachInterrupt(
    ChannelNo,
    std::bind(
      InterruptHandler,
      channelPin,
      &(OutputValue),
      &(StartValue),
      captureCompareReg,
      captureCompareEnableReg,
      captureCompareOutPolarity
    )
  );
  ChannelPin = channelPin;
  Initialized = true;
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