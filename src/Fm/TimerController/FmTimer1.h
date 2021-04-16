#ifndef FM_TIMER_1_H
#define FM_TIMER_1_H

  #include "FmTimerController.h"

  #define CH1_PIN PA8
  #define CH2_PIN PA9
  #define CH3_PIN PA10
  #define CH4_PIN PA11

  class FmTimer1 : public FmTimerController
  {
    public:
    FmTimer1() {};
    FmTimer1(HardwareTimer *timer);
    virtual void Setup();

    protected:
    virtual void SetupChannel(int channelNo);
  };

#endif