#ifndef TIMER_3_H
#define TIMER_3_H

  #include "TimerController.h"

  #define CH1_PIN PA6
  #define CH2_PIN PA7
  #define CH3_PIN PB0
  #define CH4_PIN PB1

  class Timer3 : public TimerController
  {
    public:
    Timer3() {};
    Timer3(HardwareTimer *timer);
    virtual void Setup();

    protected:
    virtual void SetupChannel(int channelNo);
  };

#endif