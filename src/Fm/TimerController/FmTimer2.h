#ifndef FM_TIMER_2_H
#define FM_TIMER_2_H

  #include "FmTimerController.h"

  #define CH1_PIN PA0
  #define CH2_PIN PA1
  #define CH3_PIN PB10
  #define CH4_PIN PB11

  class FmTimer2 : public FmTimerController
  {
    public:
    FmTimer2() {};
    FmTimer2(HardwareTimer *timer);
    virtual void Setup();

    protected:
    virtual void SetupChannel(int channelNo);
  };

#endif