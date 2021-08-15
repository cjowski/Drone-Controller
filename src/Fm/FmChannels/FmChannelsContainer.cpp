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

int32_t FmChannelsContainer::GetFmChannelValue(int channelIndex)
{
  if (channelIndex < 0 || channelIndex >= ChannelsCount)
  {
    return -1;
  }
  return Channels[channelIndex].GetValue();
}

SerialEncoderInput* FmChannelsContainer::GetSerialEncoderInput()
{
  std::list<String> texts;
  texts.push_back(String((long)millis()));
  texts.push_back(String((int)GetFmSignalState()));
  for (int i = 0; i < ChannelsCount; i++)
  {
    texts.push_back(String(Channels[i].GetValue()));
  }
  return new StringListEncoderInput(
    SERIAL_KEY,
    texts
  );
}