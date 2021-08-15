#ifndef BLUE_PILL_TIMER_2_H
#define BLUE_PILL_TIMER_2_H

  #include "Board/BoardTimer/BoardTimer.h"

  class BluePillTimer2 : public BoardTimer
  {
    private:
    static const int TIMER_CHANNELS_COUNT = 4;
    const uint8_t ChannelPins[TIMER_CHANNELS_COUNT] = {
      PA0,
      PA1,
      PA2,
      PA3
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
      return (TIM_TypeDef *) TIM2;
    };
    const uint8_t TIMER_NO() const {
      return 2;
    };
  };

#endif