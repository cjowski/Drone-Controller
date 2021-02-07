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

String FmChannelsContainer::ToSerialString()
{
  String outputString = "";
  char wordSeparator = 'a';

  outputString += "[" + String(SERIAL_PRINT_KEY) + "]";
  outputString += String(millis()) + (wordSeparator++);
  outputString += String(FmSignalActive()) + (wordSeparator++);

  for (int i = 0; i < ChannelsCount; i++) {
    outputString += String(Channels[i].GetValue());

    if (i < ChannelsCount - 1)
    {
      outputString += (wordSeparator++);
    }
  }

  return "<" + outputString + ">";
}