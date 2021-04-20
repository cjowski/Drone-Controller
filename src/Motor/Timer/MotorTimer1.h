#ifndef MOTOR_TIMER_1_H
#define MOTOR_TIMER_1_H

  #include "MotorTimerController.h"

  class MotorTimer1 : public MotorTimerController
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
    MotorTimer1() {
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
      return TIM1;
    };
  };

#endif