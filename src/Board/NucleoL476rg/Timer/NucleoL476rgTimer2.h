#ifndef NUCLEO_L476RG_TIMER_2_H
#define NUCLEO_L476RG_TIMER_2_H

  #include "Board/BoardTimer/BoardTimer.h"

  class NucleoL476rgTimer2 : public BoardTimer
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
    const uint8_t *CHANNEL_PINS() const {
      const uint8_t *array = ChannelPins;
      return array;
    };
    int CHANNELS_COUNT() const {
      return TIMER_CHANNELS_COUNT;
    };
    TIM_TypeDef *TIMER_BASE() const {
      return (TIM_TypeDef *) TIM2; //0x40000000UL + 0x00010000UL + 0x0000UL;
    };
    const uint8_t TIMER_NO() const {
      return 2;
    };
  };

#endif