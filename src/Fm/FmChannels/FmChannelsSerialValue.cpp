#include "FmChannelsSerialValue.h"

FmChannelsSerialValue::FmChannelsSerialValue(
  long time,
  int fmSignalState,
  int ch1,
  int ch2,
  int ch3,
  int ch4
)
{
  Time = time;
  FmSignalState = fmSignalState;
  ChannelValues[0] = ch1;
  ChannelValues[1] = ch2;
  ChannelValues[2] = ch3;
  ChannelValues[3] = ch4;
}

std::list<String> FmChannelsSerialValue::GetPrintStrings()
{
  std::list<String> printStrings;
  printStrings.push_back(String(Time));
  printStrings.push_back(String(FmSignalState));
  for (int i = 0; i < CHANNELS_COUNT; i++)
  {
    printStrings.push_back(String(ChannelValues[i]));
  }
  return printStrings; 
}