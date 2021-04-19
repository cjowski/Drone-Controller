#ifndef MOTOR_H
#define MOTOR_H

  #include <functional>
  #include <WSerial.h>
  #include <wiring_digital.h>
  #include <PinConfigured.h>
  #include "Serial/Printer/SerialPrintController.h"

  #define PWM_PIN PA6

  class Motor
  {
    private:
    const int MAX_SPEED = 2000;
    const int MIN_SPEED = 1000;
    const int MAX_MAP_VALUE = 2000;
    const int MIN_MAP_VALUE = 800;
    int PreviousSpeed = 1000;
    int MinChannelValue;
    int MaxChannelValue;
    std::function<bool(void)> IsFmSignalActive;
    std::function<int(void)> GetFmChannelValue;
    int GetSpeed();
    int MapFmChannelValueToSpeed(int fmChannelValue);
    HardwareTimer MotorTimer = HardwareTimer(TIM3);
    long PreviousPrintTime = 0;

    public:
    Motor(
      int minChannelValue,
      int maxChannelValue,
      std::function<bool(void)> isFmSignalActive,
      std::function<int(void)> getFmChannelValue
    );
    void SetupTimer();
    void Loop();
  };

#endif