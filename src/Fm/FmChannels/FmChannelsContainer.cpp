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

std::list<String> FmChannelsContainer::ToStringList()
{
  std::list<String> outputList;

  outputList.push_back(
    String(millis())
  );

  outputList.push_back(
    String(FmSignalState())
  );

  for (int i = 0; i < ChannelsCount; i++) {
    outputList.push_back(
      String(Channels[i].GetValue())
    );
  }

  return outputList;
}