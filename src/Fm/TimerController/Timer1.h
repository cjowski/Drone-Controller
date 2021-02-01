#ifndef TIMER_1_H
#define TIMER_1_H

  #include "TimerController.h"

  #define CH1_PIN PA8
  #define CH2_PIN PA9
  #define CH3_PIN PA10
  #define CH4_PIN PA11

  class Timer1 : public TimerController
  {
    public:
    Timer1() {};
    Timer1(HardwareTimer *timer);
    virtual void Setup();

    protected:
    virtual void SetupChannel(int channelNo);
  };

#endif