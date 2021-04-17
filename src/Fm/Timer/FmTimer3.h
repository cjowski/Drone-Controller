#ifndef FM_TIMER_3_H
#define FM_TIMER_3_H

  #include "FmTimerController.h"

  class FmTimer3 : public FmTimerController
  {
    private:
    static const int TIMER_CHANNELS_COUNT = 4;
    const uint8_t ChannelPins[TIMER_CHANNELS_COUNT] = {
      PA6,
      PA7,
      PB0,
      PB1
    };

    public:
    FmTimer3() {
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
      return TIM3;
    };
  };

#endif