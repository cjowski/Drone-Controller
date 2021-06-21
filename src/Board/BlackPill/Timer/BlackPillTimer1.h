#ifndef BLACK_PILL_TIMER_1_H
#define BLACK_PILL_TIMER_1_H

  #include "Board/BoardTimer.h"

  class BlackPillTimer1 : public BoardTimer
  {
    private:
    static const int TIMER_CHANNELS_COUNT = 4;
    const uint8_t ChannelPins[TIMER_CHANNELS_COUNT] = {
      PA8,
      PA9,
      PA10,
      PA11
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
      return (TIM_TypeDef *) TIM1;
    };
  };

#endif