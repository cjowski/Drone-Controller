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

bool FmChannelsContainer::FmSignalActive()
{
  for (int i = 0; i < ChannelsCount; i++) {
    if (!Channels[i].FmSignalActive) {
      return false;
    }
  }

  return true;
}

std::list<String> FmChannelsContainer::ToStringList()
{
  std::list<String> outputList;

  outputList.push_back(
    String(millis())
  );

  outputList.push_back(
    String(FmSignalActive())
  );

  for (int i = 0; i < ChannelsCount; i++) {
    outputList.push_back(
      String(Channels[i].GetValue())
    );
  }

  return outputList;
}