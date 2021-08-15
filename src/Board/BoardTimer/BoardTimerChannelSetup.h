#ifndef BOARD_TIMER_CHANNEL_SETUP_H
#define BOARD_TIMER_CHANNEL_SETUP_H

  #include "BoardTimer.h"

  class BoardTimerChannelSetup
  {
    private:
    uint8_t ChannelNo;
    BoardTimer *MyBoardTimer;

    public:
    BoardTimerChannelSetup(uint8_t channelNo, BoardTimer *boardTimer);
    uint8_t GetChannelNo();
    uint8_t GetTimerNo();
    TIM_TypeDef* GetTimerBase();
    uint8_t GetPin();
  };

#endif