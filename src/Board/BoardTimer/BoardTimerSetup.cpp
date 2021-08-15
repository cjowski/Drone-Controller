#include "BoardTimerSetup.h"

BoardTimerSetup::BoardTimerSetup(
  BoardTimer *boardTimer
)
{
  for (int i = 1; i <= boardTimer->CHANNELS_COUNT(); i++)
  {
    Channels.push_back(
      new BoardTimerChannelSetup(i, boardTimer)
    );
  }
}

BoardTimerSetup::BoardTimerSetup(
  std::list<BoardTimerChannelSetup*> channels
)
{
  Channels = channels;
}

int BoardTimerSetup::GetChannelsCount() const
{
  return Channels.size();
}

BoardTimerChannelSetup* BoardTimerSetup::GetChannelSetup(int channelIndex) const
{
  auto it = Channels.begin();
  std::advance(it, channelIndex);
  return *it;
}