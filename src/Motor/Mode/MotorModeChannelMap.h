#ifndef MOTOR_MODE_CHANNEL_MAP_H
#define MOTOR_MODE_CHANNEL_MAP_H

  #include <functional>
  #include "MotorMode.h"

  class MotorModeChannelMap : public MotorMode
  {
    private: 
    const int MAX_MAP_VALUE = 2000;
    const int MIN_MAP_VALUE = 800;
    int MinChannelValue;
    int MaxChannelValue;
    std::function<bool(void)> IsFmSignalActive;
    std::function<int(void)> GetFmChannelValue;
    uint32_t MapFmChannelValueToSpeed(int fmChannelValue);

    public:
    MotorModeChannelMap(
      int minChannelValue,
      int maxChannelValue,
      std::function<bool(void)> isFmSignalActive,
      std::function<int(void)> getFmChannelValue
    );
    MotorSpeed GetMotorSpeed();
  };

#endif
