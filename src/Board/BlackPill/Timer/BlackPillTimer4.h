#ifndef BLACK_PILL_TIMER_4_H
#define BLACK_PILL_TIMER_4_H

  #include "Board/BoardTimer/BoardTimer.h"

  class BlackPillTimer4 : public BoardTimer
  {
    private:
    static const int TIMER_CHANNELS_COUNT = 4;
    const uint8_t ChannelPins[TIMER_CHANNELS_COUNT] = {
      PB6,
      PB7,
      PB8,
      PB9
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
      return (TIM_TypeDef *) TIM4;
    };
    const uint8_t TIMER_NO() const {
      return 4;
    };
  };

#endif