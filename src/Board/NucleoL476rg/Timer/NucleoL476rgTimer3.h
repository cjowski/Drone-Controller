#ifndef NUCLEO_L476RG_TIMER_3_H
#define NUCLEO_L476RG_TIMER_3_H

  #include "Board/BoardTimer.h"

  class NucleoL476rgTimer3 : public BoardTimer
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
    const uint8_t *CHANNEL_PINS() const {
      const uint8_t *array = ChannelPins;
      return array;
    };
    int CHANNELS_COUNT() const {
      return TIMER_CHANNELS_COUNT;
    };
    TIM_TypeDef *TIMER_BASE() const {
      return (TIM_TypeDef *) TIM3;
    };
  };

#endif