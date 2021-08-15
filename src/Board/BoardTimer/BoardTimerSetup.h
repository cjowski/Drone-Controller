#ifndef BOARD_TIMER_SETUP_H
#define BOARD_TIMER_SETUP_H

  #include <list>
  #include <set>
  #include "BoardTimerChannelSetup.h"

  class BoardTimerSetup
  {
    private:
    std::list<BoardTimerChannelSetup*> Channels;

    public:
    BoardTimerSetup(BoardTimer *boardTimer);
    BoardTimerSetup(std::list<BoardTimerChannelSetup*> channels);
    int GetChannelsCount() const;
    BoardTimerChannelSetup* GetChannelSetup(int channelIndex) const;
  };

#endif