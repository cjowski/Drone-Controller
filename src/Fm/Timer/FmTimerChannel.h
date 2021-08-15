#ifndef FM_TIMER_CHANNEL_H
#define FM_TIMER_CHANNEL_H

  #include <pins_arduino.h>
  #include <HardwareTimer.h>
  #include <PinConfigured.h>
  #include "Board/BoardTimer/BoardTimerSetup.h"

  class FmTimerChannel
  {
    private:
    int ChannelNo;
    int TimerNo;
    uint8_t ChannelPin;
    HardwareTimer *Timer;
    int32_t StartValue = 0;
    int32_t OutputValue = 0;

    static void InterruptHandler(
      uint8_t channelPin,
      int32_t *outputValue,
      int32_t *startValue,
      volatile uint32_t *captureCompareReg,
      volatile uint32_t *captureCompareEnableReg,
      unsigned long captureCompareOutPolarity
    );

    volatile uint32_t *GetCaptureCompareRegister(TIM_TypeDef *timerBase);
    unsigned long GetCaptureCompareOutPolarity();

    public:
    FmTimerChannel(
      int channelNo,
      int timerNo,
      int channelPin,
      HardwareTimer *timer
    );
    void Setup(BoardTimerChannelSetup *channelSetup);
    int GetChannelNo();
    int GetTimerNo();
    HardwareTimer *GetTimer();
    int32_t GetOutputValue();
  };

#endif