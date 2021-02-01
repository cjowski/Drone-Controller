#ifndef TIMER_2_H
#define TIMER_2_H

  #include "TimerController.h"

  #define CH1_PIN PA0
  #define CH2_PIN PA1
  #define CH3_PIN PB10
  #define CH4_PIN PB11

  class Timer2 : public TimerController
  {
    public:
    Timer2() {};
    Timer2(HardwareTimer *timer);
    virtual void Setup();

    protected:
    virtual void SetupChannel(int channelNo);
  };

#endif