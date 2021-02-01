#ifndef TIMER_CHANNEL_H
#define TIMER_CHANNEL_H

  #include <pins_arduino.h>
  #include <HardwareTimer.h>
  #include <PinConfigured.h>

  class TimerChannel
  {
    private:
    TimerChannel() { };
    TimerChannel(int channelNo, HardwareTimer *timer);
    HardwareTimer *Timer;
    int ChannelNo;
    uint8_t ChannelPin;
    bool Initialized;
    int32_t StartValue;
    int32_t OutputValue;

    virtual void Setup(
      uint8_t channelPin,
      TimerModes_t timerMode,
      volatile uint32_t *captureCompareReg,
      volatile uint32_t *captureCompareEnableReg,
      unsigned long captureCompareOutPolarity
    );

    static void InterruptHandler(
      uint8_t channelPin,
      int32_t *outputValue,
      int32_t *startValue,
      volatile uint32_t *captureCompareReg,
      volatile uint32_t *captureCompareEnableReg,
      unsigned long captureCompareOutPolarity
    );

    friend class TimerController;
    friend class Timer1;
    friend class Timer2;
    friend class Timer3;
  };

#endif