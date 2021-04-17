#ifndef FM_TIMER_CHANNEL_H
#define FM_TIMER_CHANNEL_H

  #include <pins_arduino.h>
  #include <HardwareTimer.h>
  #include <PinConfigured.h>

  class FmTimerChannel
  {
    private:
    int ChannelNo;
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

    public:
    FmTimerChannel(
      int channelNo,
      int channelPin,
      HardwareTimer *timer
    );
    void Setup(
      volatile uint32_t *captureCompareReg,
      volatile uint32_t *captureCompareEnableReg,
      unsigned long captureCompareOutPolarity
    );
    int GetChannelNo();
    int32_t GetOutputValue();
  };

#endif