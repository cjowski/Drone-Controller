#ifndef MOTOR_H
#define MOTOR_H

  #include <functional>
  #include <WSerial.h>

  class Motor
  {
    private:
    const int MAX_SPEED = 2000;
    const int MIN_SPEED = 900;
    int PreviousSpeed = 1000;
    int MinChannelValue;
    int MaxChannelValue;
    std::function<bool(void)> IsFmSignalActive;
    std::function<int(void)> GetFmChannelValue;
    int GetSpeed();
    int MapFmChannelValueToSpeed(int fmChannelValue);

    public:
    Motor(
      int minChannelValue,
      int maxChannelValue,
      std::function<bool(void)> isFmSignalActive,
      std::function<int(void)> getFmChannelValue
    );
    void Loop();
  };

#endif