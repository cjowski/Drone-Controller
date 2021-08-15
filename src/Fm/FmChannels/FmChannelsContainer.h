#ifndef FM_CHANNELS_CONTAINER_H
#define FM_CHANNELS_CONTAINER_H

  #include <WString.h>
  #include <list>
  #include "FmChannel.h"
  #include <Serial/Type/StringList/Encoder/StringListEncoderInput.h>

  class FmChannelsContainer
  {
    private:
    int ChannelsCount = 0;
    FmChannel *Channels;
    char SERIAL_KEY = 'F';

    public:
    FmChannelsContainer(FmChannel *channels, int channelsCount);
    void UpdateChannelsValues();
    FmChannel::SignalState GetFmSignalState();
    int32_t GetFmChannelValue(int channelIndex);
    SerialEncoderInput *GetSerialEncoderInput();
  };

#endif