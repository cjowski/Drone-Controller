#ifndef FM_CHANNELS_SERIAL_VALUE_H
#define FM_CHANNELS_SERIAL_VALUE_H

  #include "Serial/Value/SerialValue.h"

  class FmChannelsSerialValue : public SerialValue
  {
    private:
    static const int CHANNELS_COUNT = 4;

    long Time;
    int FmSignalState;
    int ChannelValues[CHANNELS_COUNT];

    protected:
    bool SerialValuesMatched(std::list<String> serialValues) { return false; };

    public:
    int SERIAL_VALUES_COUNT() const { return CHANNELS_COUNT + 2; };
    char SERIAL_VALUE_KEY() const { return 'F'; };
    FmChannelsSerialValue() { };
    FmChannelsSerialValue(
      long time,
      int fmSignalState,
      int ch1,
      int ch2,
      int ch3,
      int ch4
    );
    std::list<String> GetPrintStrings();
  };

#endif