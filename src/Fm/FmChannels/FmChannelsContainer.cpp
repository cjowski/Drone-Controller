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

FmChannel::SignalState FmChannelsContainer::FmSignalState()
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

FmChannelsSerialValue* FmChannelsContainer::GetSerialValue()
{
  return new FmChannelsSerialValue(
    (long)millis(),
    (int)FmSignalState(),
    Channels[0].GetValue(),
    Channels[1].GetValue(),
    Channels[2].GetValue(),
    Channels[3].GetValue()
  );
}