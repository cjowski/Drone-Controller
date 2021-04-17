#ifndef FM_TIMER_2_H
#define FM_TIMER_2_H

  #include "FmTimerController.h"

  class FmTimer2 : public FmTimerController
  {
    private:
    static const int TIMER_CHANNELS_COUNT = 4;
    const uint8_t ChannelPins[TIMER_CHANNELS_COUNT] = {
      PA0,
      PA1,
      PB10,
      PB11
    };

    public:
    FmTimer2() {
      Timer = new HardwareTimer(this->TIMER_BASE());
    };
    const uint8_t *CHANNEL_PINS() const {
      const uint8_t *array = ChannelPins;
      return array;
    };
    int CHANNELS_COUNT() const {
      return TIMER_CHANNELS_COUNT;
    };
    TIM_TypeDef *TIMER_BASE() const {
      return TIM2;
    };
  };

#endif