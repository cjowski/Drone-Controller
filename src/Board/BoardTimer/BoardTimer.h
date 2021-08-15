#ifndef BOARD_TIMER_H
#define BOARD_TIMER_H

  #include <HardwareTimer.h>

  class BoardTimer
  {
    public:
    virtual const uint8_t *CHANNEL_PINS() const = 0;
    virtual int CHANNELS_COUNT() const = 0;
    virtual TIM_TypeDef *TIMER_BASE() const = 0;
    virtual const uint8_t TIMER_NO() const = 0;
  };

#endif