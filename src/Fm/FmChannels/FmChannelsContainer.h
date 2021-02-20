#ifndef FM_CHANNELS_CONTAINER_H
#define FM_CHANNELS_CONTAINER_H

  #include <WString.h>
  #include <list>
  #include "FmChannel.h"

  class FmChannelsContainer
  {
    private:
    int ChannelsCount = 0;
    FmChannel *Channels;

    public:
    FmChannelsContainer(FmChannel *channels, int channelsCount);
    void UpdateChannelsValues();
    FmChannel::SignalState FmSignalState();
    std::list<String> ToStringList();
  };

#endif