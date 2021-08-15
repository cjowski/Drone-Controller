#ifndef BLACK_PILL_TIMER_2_H
#define BLACK_PILL_TIMER_2_H

  #include "Board/BoardTimer/BoardTimer.h"

  class BlackPillTimer2 : public BoardTimer
  {
    private:
    static const int TIMER_CHANNELS_COUNT = 4;
    const uint8_t ChannelPins[TIMER_CHANNELS_COUNT] = {
      PA5,
      PB3,
      PB10,
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