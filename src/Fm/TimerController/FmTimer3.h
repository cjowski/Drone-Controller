#ifndef FM_TIMER_3_H
#define FM_TIMER_3_H

  #include "FmTimerController.h"

  #define CH1_PIN PA6
  #define CH2_PIN PA7
  #define CH3_PIN PB0
  #define CH4_PIN PB1

  class FmTimer3 : public FmTimerController
  {
    public:
    FmTimer3() {};
    FmTimer3(HardwareTimer *timer);
    virtual void Setup();

    protected:
    virtual void SetupChannel(int channelNo);
  };

#endif