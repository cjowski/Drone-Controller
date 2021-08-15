#include "BoardTimerChannelSetup.h"

BoardTimerChannelSetup::BoardTimerChannelSetup(
  uint8_t channelNo,
  BoardTimer *boardTimer
)
{
  ChannelNo = channelNo;
  MyBoardTimer = boardTimer;
}

uint8_t BoardTimerChannelSetup::GetChannelNo()
{
  return ChannelNo;
}

uint8_t BoardTimerChannelSetup::GetTimerNo()
{
  return MyBoardTimer->TIMER_NO();
}

TIM_TypeDef* BoardTimerChannelSetup::GetTimerBase()
{
  return MyBoardTimer->TIMER_BASE();
}

uint8_t BoardTimerChannelSetup::GetPin()
{
  return MyBoardTimer->CHANNEL_PINS()[ChannelNo - 1];
}