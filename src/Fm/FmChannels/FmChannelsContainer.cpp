#include "FmChannelsContainer.h"

FmChannelsContainer::FmChannelsContainer(FmChannel *channels, int channelsCount)
{
  ChannelsCount = channelsCount;
  Channels = channels;
}

void FmChannelsContainer::UpdateChannelsValues()
{
  for (int i = 0; i < ChannelsCount; i++) {
    Channels[i].ProcessUpdateValueCallback();
  }
}

FmChannel::SignalState FmChannelsContainer::GetFmSignalState()
{
  int activeChannelsCount = 0;
  for (int i = 0; i < ChannelsCount; i++) {
    if (Channels[i].FmSignalState == FmChannel::SignalState::inactive) {
      return FmChannel::SignalState::inactive;
    }
    else if (Channels[i].FmSignalState == FmChannel::SignalState::active) {
      activeChannelsCount++;
    }
  }

  if (activeChannelsCount == ChannelsCount)
  {
    return FmChannel::SignalState::active;
  }
  return FmChannel::SignalState::restoring;
}

int32_t FmChannelsContainer::GetFmChannelValue(int channelNo)
{
  if (channelNo < 0 || channelNo >= ChannelsCount)
  {
    return -1;
  }
  return Channels[channelNo].GetValue();
}

FmChannelsSerialValue* FmChannelsContainer::GetSerialValue()
{
  return new FmChannelsSerialValue(
    (long)millis(),
    (int)GetFmSignalState(),
    Channels[0].GetValue(),
    Channels[1].GetValue(),
    Channels[2].GetValue(),
    Channels[3].GetValue()
  );
}