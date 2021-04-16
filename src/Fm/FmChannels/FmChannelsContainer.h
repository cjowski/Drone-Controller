#ifndef FM_CHANNELS_CONTAINER_H
#define FM_CHANNELS_CONTAINER_H

  #include <WString.h>
  #include <list>
  #include "FmChannel.h"
  #include "FmChannelsSerialValue.h"

  class FmChannelsContainer
  {
    private:
    int ChannelsCount = 0;
    FmChannel *Channels;

    public:
    FmChannelsContainer(FmChannel *channels, int channelsCount);
    void UpdateChannelsValues();
    FmChannel::SignalState GetFmSignalState();
    int32_t GetFmChannelValue(int channelNo);
    FmChannelsSerialValue *GetSerialValue();
  };

#endif